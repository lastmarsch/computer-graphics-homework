#ifndef CHANGEPOINT_H
#define CHANGEPOINT_H

#include <QDialog>

namespace Ui {
class ChangePoint;
}

class ChangePoint : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePoint(QWidget *parent = nullptr, int id = 0);
    ~ChangePoint();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

signals:
    void changeItem(int id, double x, double y, double z);

private:
    Ui::ChangePoint *ui;
    int id;
};

#endif // CHANGEPOINT_H
