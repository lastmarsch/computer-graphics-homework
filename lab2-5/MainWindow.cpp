#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <set>
#include "math.h"
#include "changepoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graphicsScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(graphicsScene);
    QBrush brush = QBrush(Qt::gray, Qt::CrossPattern);
    graphicsScene->setBackgroundBrush(brush);
    graphicsScene->setSceneRect(-385, -230, 770, 460);
    graphicsScene->installEventFilter(this);
    ui->graphicsView->scale(1, -1);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    connect(this, SIGNAL(run()), SLOT(bezier()));
    printAxis();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) {

    if (target == graphicsScene) {
        if (event->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *)event;
            QPointF position = mouseEvent->scenePos();
            qDebug() << position;
            addPointToTable(position);
            return true;
        }
    }
    return QMainWindow::eventFilter(target, event);
}

void MainWindow::printAxis()
{
    // отрисовка осей (для наглядности)
    graphicsScene->addLine(0, -230, 0, 230, QPen(Qt::red, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    graphicsScene->addLine(-385, 0, 385, 0, QPen(Qt::red, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
}

void MainWindow::addPointToTable(QPointF point)
{
    const int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(currentRow + 1);

    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString("(%1, %2)")
                                                                 .arg(QString::number(point.x()))
                                                                 .arg(QString::number(point.y()))));
}

void MainWindow::on_pushButton_2_clicked()
{
    std::set<int, std::greater<int>> selectedRows;
    auto itemList = ui->tableWidget->selectedItems();
    for (auto& item : itemList)
    {
        selectedRows.insert(item->row());
    }
    for (int row : selectedRows)
    {
        ui->tableWidget->removeRow(row);
    }
    graphicsScene->clear();
    printAxis();
}

void MainWindow::on_pushButton_clicked()
{
    graphicsScene->clear();
    printAxis();
    points.clear();

    if (ui->tableWidget->rowCount() < 3) {
        ui->_warning->setText(QString("Number cannot be less than 3.").toUtf8());
        return;
    }
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            QPointF p = fromBracketsToPoint(ui->tableWidget->item(i, j)->text());
            points.append(p);
        }
    }
    //    std::sort(points.begin(), points.end(), compare);
    drawLine();
}

QPointF MainWindow::fromBracketsToPoint(QString str)
{
    QStringList temp = str.trimmed().remove("(").remove(")").split(",");
    if (temp.size() != 2) {
        ui->_warning->setText(QString("Parse error.").toUtf8());
        return QPointF();
    }
    QPointF point;
    point = QPointF(temp[0].toDouble(), temp[1].toDouble());
    return point;
}

void MainWindow::drawLine()
{
    if (points.size() < 2) {
        ui->_warning->setText(QString("Array error.").toUtf8());
        return;
    }

    line = QPainterPath(points[0]);

    for (int i = 1; i < points.size(); i++)
        line.lineTo(points[i]);
    graphicsScene->addPath(line, QPen(Qt::gray, 3));

    for (int i = 0; i < points.size(); i++) {
        double rad = 1;
        graphicsScene->addEllipse(points[i].x()-rad, points[i].y()-rad, rad*2.0, rad*2.0,
                                  QPen(Qt::black, 3), QBrush(Qt::SolidPattern));
    }
    emit run();
}

bool MainWindow::compare(const QPointF& first, const QPointF& second)
{
    if (first.x() < second.x())
        return true;
    else if (first.x() > second.x())
        return false;
    else
    {
        if (first.y() < second.y())
            return true;
        else
            return false;
    }
}

int factorial(qint64 n)
{
    qint64 ret = 1;
    for(qint64 i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

double bernstein(qint64 i, qint64 n, qreal t)
{
    return (factorial(n)/(factorial(i)*factorial(n-i))) * std::pow(t, i) * std::pow(1-t, n-i);
}

void MainWindow::bezier()
{
    QList<QPointF> temp;
    QPointF bufpoint1(points.first().x(), points.first().y()), bufpoint2;
    temp.append(bufpoint1);
    for(double t = 0; t <= 1; t += 0.01){
        bufpoint2 = QPointF(0,0);
        for(int i = 0; i < points.size(); ++i)
        {
            QPointF curPoint(points.at(i).x(), points.at(i).y());
            bufpoint2 += bernstein(i, points.size() - 1, t) * curPoint;
        }
        temp.append(bufpoint2);
        bufpoint1 = bufpoint2;
    }

    for (int i = 1; i < temp.size(); i ++)
        graphicsScene->addLine(temp[i - 1].x(), temp[i - 1].y(), temp[i].x(), temp[i].y(),
                QPen(Qt::red, 3));
}

void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    ChangePoint * chP = new ChangePoint(this, item->row());
    connect(chP, SIGNAL(changeItem(int, double, double)), this, SLOT(change(int, double, double)));
    chP->show();
}

void MainWindow::change(int id, double x, double y)
{
    if (id > points.size())
        return;
    ui->tableWidget->item(id, 0)->setText(QString("(%1, %2)")
                                          .arg(QString::number(x))
                                          .arg(QString::number(y)));
    on_pushButton_clicked();
}
