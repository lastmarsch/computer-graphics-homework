#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QKeyEvent>
#include "quaternion.h"

class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
//    void wheelEvent(QWheelEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void drawAxis();
    void drawSurface();
    void normalize(QVector3D point);

public slots:
    void drawing(QList<QVector3D>, double xR, double yR);
    void keyPressEvent(QKeyEvent *event);

private:
    QPointF mousePos;
    int scale;
    int xRotation, yRotation, zRotation;
    double xFigureRotation, yFigureRotation;
    QList<QVector3D> points;
};

#endif // OPENGLWIDGET_H
