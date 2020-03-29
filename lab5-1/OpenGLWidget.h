#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QKeyEvent>
#include "quaternion.h"

typedef QList<QVector3D> face;

class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void drawAxis();
    void roberts(QVector3D V1, QVector3D V2, QVector3D V3, QVector3D P, QVector3D W);

public slots:
    void keyPressEvent(QKeyEvent *event);

private:
    QPointF mousePos;
    int scale;
    int xRotation, yRotation, zRotation;
    face points;
};

#endif // OPENGLWIDGET_H
