#ifndef ADDPOINT_H
#define ADDPOINT_H

#include <QDialog>

namespace Ui {
class AddPoint;
}

class AddPoint : public QDialog
{
    Q_OBJECT

public:
    explicit AddPoint(QWidget *parent = nullptr);
    ~AddPoint();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

signals:

    void addItem(double x, double y, double z);

private:
    Ui::AddPoint *ui;
};

#endif // ADDPOINT_H
