#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QKeyEvent>
#include <vec3f.h>
typedef Vec3<GLfloat> Vec3f;

class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void cyrusBeck(Vec3f p0, Vec3f p1, Vec3f &q0, Vec3f &q1);

public slots:
    void drawing(QList<Vec3f> &, double num);

private:
    int number;
    QList<Vec3f> points;
};

#endif // OPENGLWIDGET_H
