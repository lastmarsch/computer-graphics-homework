#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "OpenGLWidget.h"
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_del_clicked();

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_surface_clicked();

public slots:

    void add(double, double);

    void change(int id, double x, double y);

signals:

    void draw(QList<QPointF>&, double num);

private:
    Ui::MainWindow *ui;
    OpenGLWidget * w;

    QList<QPointF> points;
};
#endif // MAINWINDOW_H
