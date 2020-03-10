#include "OpenGLWidget.h"
#include <QDebug>


OpenGLWidget::OpenGLWidget()
{
    resize(800, 600);
    xRotation = 0;
    yRotation = 0;
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
    //    gluLookAt(3.0, 3.0, 3.0-4.5, 0.0, 0.0, -4.5, 0, 1, 0);
    glLoadIdentity();           // загрузка единичную матрицу
    glScalef(scale, scale, scale);        // масштабирование
    glRotatef(xRotation, 1.0f, 0.0f, 0.0f); // поворот по X
    glRotatef(yRotation, 0.0f, 1.0f, 0.0f); // поворот по Y
    glRotatef(zRotation, 0.0f, 0.0f, 1.0f); // поворот по Z
    drawAxis();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    // запоминаем координату нажатия мыши
    mousePos = pe->pos();
    qDebug() << mousePos;
}

//void OpenGLWidget::wheelEvent(QWheelEvent* pe) // вращение колёсика мыши
//{
//    // если колесико вращаем вперед -- умножаем переменную масштаба на 1.1
//    // иначе -- делим на 1.1
//    if (pe->delta() > 0)
//        scale *= 1.1;
//    else if (pe->delta() < 0)
//        scale /= 1.1;

//    updateGL();
//}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* pe) // изменение положения стрелки мыши
{
    xRotation += 180/scale * (GLfloat)(pe->y()-mousePos.y()) / height(); // вычисляем углы поворота
    zRotation += 180/scale * (GLfloat)(pe->x()-mousePos.x()) / width();

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
