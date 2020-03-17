#include "OpenGLWidget.h"
#include <QDebug>
#include <math.h>

OpenGLWidget::OpenGLWidget()
{
    number = 0;
    resize(800, 800);
}

void OpenGLWidget::initializeGL()
{

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 0, 0);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
}

void OpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);

    glViewport(0, 0, w, h); // установка точки обзора
    glMatrixMode(GL_PROJECTION); // установка режима матрицы
    glLoadIdentity(); // загрузка матрицы
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана
    glMatrixMode(GL_MODELVIEW); // задаем модельно-видовую матрицу
    glLoadIdentity();           // загрузка единичную матрицу

    glColor3f(0.0f, 0.5f, 0.5f);//Blue-Green
    glBegin(GL_LINES);
    foreach(QPointF point, points)
        glVertex3d(point.x(), point.y(), 0);
    glEnd();

}

void OpenGLWidget::drawing(QList<QPointF>& ps, double num)
{
    points = ps;
    number = num;
    qDebug() << points;
    updateGL();
}



