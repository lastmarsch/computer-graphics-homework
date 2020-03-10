#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>

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
private:
    QPointF mousePos;
    int scale;
    int xRotation, yRotation, zRotation;
};

#endif // OPENGLWIDGET_H
