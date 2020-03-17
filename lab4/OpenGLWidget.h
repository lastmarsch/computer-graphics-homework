#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QKeyEvent>

class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void drawing(QList<QPointF>&, double num);

private:
    int number;
    QList<QPointF> points;
};

#endif // OPENGLWIDGET_H
