#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QDebug>
#include <limits.h>


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

bool MainWindow::eventFilter(QObject *target, QEvent *event) {

    if (target == graphicsScene) {
        if (event->type() == QEvent::GraphicsSceneMousePress) {
            QGraphicsSceneMouseEvent *mouseEvent = (QGraphicsSceneMouseEvent *)event;
            QPointF position = mouseEvent->scenePos();
            qDebug() << position;
            return true;
        }
    }
    return QMainWindow::eventFilter(target, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    graphicsScene->clear();
    printAxis();
    ui->warning->clear();
    ui->textBrowser->clear();

    if (ui->_r->text().isEmpty()) {
        ui->warning->setText("Радиус не может быть равным нулю.");
        return;
    }
    if (ui->_r->text().toInt() < 0) {
        ui->warning->setText("Радиус не может быть отрицательным.");
        return;
    }
    double x = ui->_x->text().toDouble();
    double y = ui->_y->text().toDouble();
    double r = ui->_r->text().toDouble();
    double xt = ui->_xt->text().toDouble();
    double yt = ui->_yt->text().toDouble();
    if (x > 385 || x < -385 || xt > 385 || xt < -385) {
        ui->warning->setText("Значение X точки не соответствует диапазону (-385, 385).");
        return;
    }
    if (y > 230 || y < -230 || yt > 230 || yt < -230) {
        ui->warning->setText("Значение Y точки не соответствует диапазону (-230, 230).");
        return;
    }
    if ((x + r) > 385 || (x - r) < -385 ||
            (y + r) > 385 || (y - r) < -385) {
        ui->warning->setText("Значение радиуса выходит из диапазона.");
        return;
    }
    if (x > 385 || x < -385) {
        ui->warning->setText("Значение точки не соответствует диапазону (-385, 385).");
        return;
    }
    if (x > 385 || x < -385) {
        ui->warning->setText("Значение точки не соответствует диапазону (-385, 385).");
        return;
    }

    if (checkInCircle(x, y, r, xt, yt)) {
        ui->warning->setText("Заданная точка находится внутри окружности. Нельзя построить касательную.");
        return;
    }

    this->_x = x;
    this->_y = y;
    this->_r = r;
    this->_xt = xt;
    this->_yt = yt;

    // создание и отрисовка круга
    circle = new QGraphicsEllipseItem(x - r, y - r, 2*r, 2*r);
    circle->setPen(QPen(Qt::blue, 2));
    graphicsScene->addItem(circle);

    // создание и отрисовка точки
    point = QPointF(xt, yt);
    double rad = 1;
    graphicsScene->addEllipse(point.x()-rad, point.y()-rad, rad*2.0, rad*2.0,
                              QPen(Qt::red, 3), QBrush(Qt::SolidPattern));

    drawTangent();
}

bool MainWindow::checkInCircle(double x, double y, double r, double x_t, double y_t)
{
    // если расстояние чежду точкой и центром меньше радиуса окружности, возвращает true
    double between_r = range(x, y, x_t, y_t);
    if (between_r >= r)
        return false;
    return true;
}

double MainWindow::range(double x, double y, double x_t, double y_t)
{
    return (std::sqrt(std::pow(x - x_t, 2) + std::pow(y - y_t, 2)));
}

void MainWindow::printAxis()
{
    // отрисовка осей (для наглядности)
    graphicsScene->addLine(0, -230, 0, 230, QPen(Qt::red, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    graphicsScene->addLine(-385, 0, 385, 0, QPen(Qt::red, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
}

void MainWindow::drawTangent()
{    
    QList<QPointF> points = calcPoint();
    if (points == QList<QPointF>()) {
        ui->warning->setText("Произошла ошибка в вычислении точек касания.");
        return;
    }

    foreach (QPointF p, points) {
        ui->textBrowser->append(QString("X: %1; Y: %2")
                                .arg(QString::number(p.x()))
                                .arg(QString::number(p.y())));
        graphicsScene->addLine(point.x(), point.y(), p.x(), p.y(), QPen(Qt::black, 2));
        double rad = 1;
        graphicsScene->addEllipse(p.x()-rad, p.y()-rad, rad*2.0, rad*2.0,
                                  QPen(Qt::green, 3), QBrush(Qt::SolidPattern));
    }

    double rad = 1;
    graphicsScene->addEllipse(point.x()-rad, point.y()-rad, rad*2.0, rad*2.0,
                              QPen(Qt::red, 3), QBrush(Qt::SolidPattern));
}

QList<QPointF> MainWindow::calcPoint()
{
    QList<QPointF> list;

    double diameter = range(_x, _y, _xt, _yt);
    QPointF newCenter;
    newCenter.setX((_x + _xt) / 2);
    newCenter.setY((_y + _yt) / 2);

    QGraphicsEllipseItem * newCircle = new QGraphicsEllipseItem(newCenter.x() - diameter / 2,
                                                                newCenter.y() - diameter / 2,
                                                                diameter,
                                                                diameter);
    newCircle->setPen(QPen(Qt::gray));
    graphicsScene->addItem(newCircle);

    double r = diameter / 2;
    double r2d = r * r;
    double r4d = r2d * r2d;
    double rASquared = r * r;
    double rBSquared = _r * _r;
    double a = (rASquared - rBSquared) / (2 * r2d);
    double r2r2 = (rASquared - rBSquared);
    double c = std::sqrt(2 * (rASquared + rBSquared) / r2d - (r2r2 * r2r2) / r4d - 1);

    double fx = (newCenter.x() + _x) / 2 + a * (_x - newCenter.x());
    double gx = c * (_y - newCenter.y()) / 2;
    double ix1 = fx + gx;
    double ix2 = fx - gx;

    double fy = (newCenter.y() + _y) / 2 + a * (_y - newCenter.y());
    double gy = c * (newCenter.x() - _x) / 2;
    double iy1 = fy + gy;
    double iy2 = fy - gy;

    if (std::abs(gx) <  std::numeric_limits<double>::epsilon()
            && std::abs(gy) < std::numeric_limits<double>::epsilon()) {
        list.append(QPointF(ix1, iy1));
    }
    else {
        list.append(QPointF(ix1, iy1));
        list.append(QPointF(ix2, iy2));
    }
    return list;
}




