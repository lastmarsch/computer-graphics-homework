#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "addpoint.h"
#include "changepoint.h"
#include <set>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    w = new OpenGLWidget();
    connect(this, &MainWindow::draw, w, &OpenGLWidget::drawing);
    w->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    AddPoint * ap = new AddPoint(this);
    connect(ap, SIGNAL(addItem(double, double)), this, SLOT(add(double, double)));
    ap->show();
}

void MainWindow::add(double x, double y)
{
    const int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(currentRow + 1);

    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString("(%1, %2)")
                                                                 .arg(QString::number(x))
                                                                 .arg(QString::number(y))));

    points.push_back(Vec3f(x, y, 0));
}

void MainWindow::on_del_clicked()
{

    std::set<int, std::greater<int>> selectedRows;
    auto itemList = ui->tableWidget->selectedItems();
    if (itemList.isEmpty())
        return;
    for (auto& item : itemList)
    {
        selectedRows.insert(item->row());
    }
    for (int row : selectedRows)
    {
        ui->tableWidget->removeRow(row);
        points.removeAt(row);
    }
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
    points[id] = Vec3f(x, y, 0);
}

void MainWindow::on_surface_clicked()
{
    if (points.size() < 3) {
        QMessageBox::warning(this, "Ошибка", "Для построения нужны как минимум 3 точки.");
        return;
    }

    qDebug() << points;
    emit draw(points, ui->num->text().toDouble());
}
