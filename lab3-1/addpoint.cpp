#include "addpoint.h"
#include "ui_addpoint.h"

AddPoint::AddPoint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPoint)
{
    ui->setupUi(this);
}

AddPoint::~AddPoint()
{
    delete ui;
}

void AddPoint::on_buttonBox_accepted()
{
    double x = ui->_x->text().toDouble();
    double y = ui->_y->text().toDouble();
    double z = ui->_z->text().toDouble();
    emit(addItem(x, y, z));

    on_buttonBox_rejected();
}

void AddPoint::on_buttonBox_rejected()
{
    this->deleteLater();
    this->close();
}
