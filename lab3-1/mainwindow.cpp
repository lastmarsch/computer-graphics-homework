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
    connect(this, &MainWindow::draw,  w, &OpenGLWidget::drawing);
    w->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    if (points.size() > 3) {
        QMessageBox::warning(this, "Ошибка", "Нельзя добавить точку.");
        return;
    }

    AddPoint * ap = new AddPoint(this);
    connect(ap, SIGNAL(addItem(double, double, double)), this, SLOT(add(double, double, double)));
    ap->show();
}

void MainWindow::add(double x, double y, double z)
{
    const int currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(currentRow + 1);

    ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString("(%1, %2, %3)")
                                                                 .arg(QString::number(x))
                                                                 .arg(QString::number(y))
                                                                 .arg(QString::number(z))));

    points.push_back(QVector3D(x, y, z));
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
    connect(chP, SIGNAL(changeItem(int, double, double, double)), this, SLOT(change(int, double, double, double)));
    chP->show();
}

void MainWindow::change(int id, double x, double y, double z)
{
    if (id > points.size())
        return;
    ui->tableWidget->item(id, 0)->setText(QString("(%1, %2, %3)")
                                          .arg(QString::number(x))
                                          .arg(QString::number(y))
                                          .arg(QString::number(z)));
    points[id] = QVector3D(x, y, z);
}

void MainWindow::on_surface_clicked()
{
    if (points.size() < 3) {
        QMessageBox::warning(this, "Ошибка", "Для построения нужны 4 точки.");
        return;
    }

    qDebug() << points;
    emit draw(points, ui->xR->text().toDouble(), ui->yR->text().toDouble());
}
