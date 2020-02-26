#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
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

    bool eventFilter(QObject *target, QEvent *event);
    void printAxis();
    void addPointToTable(QPointF point);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void bezier();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void change(int id, double x, double y);

signals:
    void run();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *graphicsScene;
    QList<QPointF> points;
    QPainterPath line;

    QPointF fromBracketsToPoint(QString str);
    void drawLine();
    /*!
     * \brief compare Компаратор для сортировки QPointF.
     *                Не использовался, но пусть будет.
     * \param first
     * \param second
     * \return
     */
    static bool compare(const QPointF& first, const QPointF& second);

};
#endif // MAINWINDOW_H
