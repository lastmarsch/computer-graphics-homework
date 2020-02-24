#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    /*!
     * \brief eventFilter Ловит event QEvent::GraphicsSceneMousePress от QGraphicsScene.
     *                    Для удобства пишет в консоль координаты на сцене по клику мыши.
     * \param target
     * \param event
     * \return
     */
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    /*!
     * \brief on_pushButton_clicked Запись, обработка того, что вводит пользователь,
     *                              вызов drawTangent().
     */
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * graphicsScene;
    QGraphicsEllipseItem * circle;
    QPointF point;
    double _x, _y, _r;
    double _xt, _yt;

    /*!
     * \brief checkInCircle Находится ли точка внутри круга.
     * \param x             Центр круга
     * \param y             Центр круга
     * \param r             Радиус круга
     * \param x_t           Координата точки
     * \param y_t           Координата точки
     * \return
     */
    bool checkInCircle(double x,
                       double y,
                       double r,
                       double x_t,
                       double y_t);

    double range(double x,
                 double y,
                 double x_t,
                 double y_t);
    /*!
     * \brief printAxis Вывод осей X и Y на экран. Чисто косметическая функция.
     */
    void printAxis();
    /*!
     * \brief drawTangent Отрисовка полученных из calcPoint() точек и линий к ним.
     */
    void drawTangent();
    /*!
     * \brief calcPoint Математическое вычисление точек пересечения двух окружностей.
     * \return Список из полученных точек, размера:
     *              0 - произошла ошибка,
     *              1 - соприкасаются в одной точке,
     *              2 - соприкасаются в двух точках.
     */
    QList<QPointF> calcPoint();

};
#endif // MAINWINDOW_H
