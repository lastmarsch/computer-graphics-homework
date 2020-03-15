#include "OpenGLWidget.h"
#include <QDebug>
#include <math.h>
#include <QQuaternion>

OpenGLWidget::OpenGLWidget()
{
    resize(800, 800);
    xRotation = xFigureRotation = 0;
    yRotation = yFigureRotation = 0;
    zRotation = 0;
    scale = 1;
}

void OpenGLWidget::initializeGL()
{
    qglClearColor(Qt::white); // заполняем экран белым цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
    glEnable(GL_CULL_FACE); // говорим, что будем строить только внешние поверхности
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // фигуры будут закрашены с обеих сторон
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    glScalef(scale, scale, scale);        // масштабирование
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z
    drawAxis();

    glPointSize(4);
    glColor3b(1,0,0);
    glBegin (GL_POINTS);
    for (int i = 0; i < points.size(); i++) {
        glVertex3f(points[i].x(), points[i].y(), points[i].z());
    }
    glEnd();
    drawSurface();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    // запоминаем координату нажатия мыши
    mousePos = pe->pos();
    qDebug() << mousePos;
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{
    xRotation += 180 / scale * (GLfloat)(pe->y() - mousePos.y()) / height(); // вычисляем углы поворота
    zRotation += 180 / scale * (GLfloat)(pe->x() - mousePos.x()) / width();

    mousePos = pe->pos();

    updateGL(); // обновляем изображение
}

void OpenGLWidget::drawAxis()
{
    glLineWidth(3.0f); // устанавливаем ширину линии

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих линий
    // ось x
    glBegin(GL_LINES); // построение линии
    glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
    glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
    // ось y
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 0.0f, -1.0f,  0.0f);

    glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
    // ось z
    glVertex3f( 0.0f,  0.0f,  1.0f);
    glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}

void OpenGLWidget::drawSurface()
{
    if (points.size() != 4)
        return;
    qglColor(Qt::magenta);
    glPointSize(3);
    glBegin(GL_POINTS);
    for (double u = 0; u < 1; u += 0.01)
        for (double v = 0; v < 1; v += 0.01) {
            QVector3D r = (1 - u) * (1 - v) * points[0]
                    + u * (1 - v) * points[1]
                    + (1 - u) * v * points[2]
                    + u * v * points[3];
            glVertex3f(r.x(), r.y(), r.z());
        }
    glEnd();
}

void OpenGLWidget::drawing(QList<QVector3D> ps, double xR, double yR)
{
    points = ps;
    xFigureRotation = xR;
    yFigureRotation = yR;
    qDebug() << points;
    updateGL();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    QQuaternion q;

    if (event->key() == Qt::Key_Y) { //вращение по у
        q = QQuaternion::fromEulerAngles(0, yFigureRotation, 0);
    }
    if (event->key() == Qt::Key_X) { //вращение по х
        q = QQuaternion::fromEulerAngles(xFigureRotation, 0, 0);
    }
    if (event->key() == Qt::Key_Up) { //вращение по y
        q = QQuaternion::fromEulerAngles(0, 5, 0);
    }
    if (event->key() == Qt::Key_Down) { //вращение по y
        q = QQuaternion::fromEulerAngles(0, -5, 0);
    }
    if (event->key() == Qt::Key_Right) { //вращение по х
        q = QQuaternion::fromEulerAngles(5, 0, 0);
    }
    if (event->key() == Qt::Key_Left) { //вращение по х
        q = QQuaternion::fromEulerAngles(-5, 0, 0);
    }

    for (int i = 0; i < points.size(); i++)
        points[i] = Quaternion::transformVec(q, points[i]);

    updateGL();
}

