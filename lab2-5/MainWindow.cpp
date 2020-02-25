#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <set>

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
            if (p != QPointF())
                points.append(p);
        }
    }
    std::sort(points.begin(), points.end(), compare);
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
    graphicsScene->addPath(line, QPen(Qt::red, 3));
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
