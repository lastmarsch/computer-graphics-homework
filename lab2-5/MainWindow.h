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

    /*!
     * \brief eventFilter Ловит event QEvent::GraphicsSceneMousePress от QGraphicsScene.
     *                    Для удобства пишет в консоль координаты на сцене по клику мыши.
     * \param target
     * \param event
     * \return
     */
    bool eventFilter(QObject *target, QEvent *event);
    /*!
     * \brief printAxis Вывод осей X и Y на экран. Чисто косметическая функция.
     */
    void printAxis();
    void addPointToTable(QPointF point);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *graphicsScene;
    QList<QPointF> points;
    QPainterPath line;

    QPointF fromBracketsToPoint(QString str);
    void drawLine();
    static bool compare(const QPointF& first, const QPointF& second);
};
#endif // MAINWINDOW_H
