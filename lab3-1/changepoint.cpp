#include "changepoint.h"
#include "ui_changepoint.h"

ChangePoint::ChangePoint(QWidget *parent, int id) :
    QDialog(parent),
    ui(new Ui::ChangePoint)
{
    ui->setupUi(this);
    this->id = id;
}

ChangePoint::~ChangePoint()
{
    delete ui;
}

void ChangePoint::on_buttonBox_rejected()
{
    this->deleteLater();
    this->close();
}

void ChangePoint::on_buttonBox_accepted()
{
    double x = ui->_x->text().toDouble();
    double y = ui->_y->text().toDouble();
    double z = ui->_z_2->text().toDouble();
    emit(changeItem(id, x, y, z));

    on_buttonBox_rejected();
}
