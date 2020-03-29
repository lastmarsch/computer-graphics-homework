#include "OpenGLWidget.h"
#include <QDebug>
#include <QQuaternion>
#include <math.h>

OpenGLWidget::OpenGLWidget()
{
    resize(800, 800);
    xRotation = 0;
    yRotation = 0;
    zRotation = 0;
    scale = 1;

    // cube points
    points.append(QVector3D(0, 0, 0));       //0
    points.append(QVector3D(0.5, 0, 0));     //1
    points.append(QVector3D(0, 0.5, 0));     //2
    points.append(QVector3D(0, 0, 0.5));     //3
    points.append(QVector3D(0.5, 0, 0.5));   //4
    points.append(QVector3D(0, 0.5, 0.5));   //5
    points.append(QVector3D(0.5, 0.5, 0));   //6
    points.append(QVector3D(0.5, 0.5, 0.5)); //7
}

void OpenGLWidget::initializeGL()
{
    qglClearColor(Qt::white); // заполняем экран белым цветом
    glEnable(GL_DEPTH_TEST); // задаем глубину проверки пикселей
    glShadeModel(GL_FLAT); // убираем режим сглаживания цветов
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

//bool OpenGLWidget::Roberts_alg(vertex V1, vertex V2, vertex V3, view_point P, barycenter W)
//	{
//		vector_u Vec1, Vec2;
//		//
//		// for this face we find the coordinates of two vectors
//		// that lie in the plane of the face
//		//
//		Vec1.X = V1.X - V2.X;
//		Vec2.X = V3.X - V2.X;
//		Vec1.Y = V1.Y - V2.Y;
//		Vec2.Y = V3.Y - V2.Y;
//		Vec1.Z = V1.Z - V2.Z;
//		Vec2.Z = V3.Z - V2.Z;
//		//
//		// calculate the coefficients of the equation of the plane
//		//
//		double A, B, C, D;
//		A = Vec1.Y * Vec2.Z - Vec2.Y * Vec1.Z;
//		B = Vec1.Z * Vec2.X - Vec2.Z * Vec1.X;
//		C = Vec1.X * Vec2.Y - Vec2.X * Vec1.Y;
//		D = -(A * V1.X + B * V1.Y + C * V1.Z);
//		//
//		// coefficient changing the sign of the plane
//		//
//		double m;
//		if ((A * W.X + B * W.Y + C * W.Z + D) < 0) m = 1.0;
//		else if ((A * W.X + B * W.Y + C * W.Z + D) > 0) m = -1.0;
//		else m = 0.0;
//		//
//		// adjust the direction of the plane
//		//
//		A *= m;
//		B *= m;
//		C *= m;
//		D *= m;

//		if ((A * P.X + B * P.Y + C * P.Z + D) > 0)
//			return 0;
//		else return 1;
//	}
//}

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


    glLineWidth(2.0f);
    glBegin(GL_QUADS);

    qglColor(Qt::magenta);
    glVertex3f(points[0].x(), points[0].y(), points[0].z());
    glVertex3f(points[3].x(), points[3].y(), points[3].z());
    glVertex3f(points[4].x(), points[4].y(), points[4].z());
    glVertex3f(points[1].x(), points[1].y(), points[1].z());

    qglColor(Qt::cyan);
    glVertex3f(points[0].x(), points[0].y(), points[0].z());
    glVertex3f(points[3].x(), points[3].y(), points[3].z());
    glVertex3f(points[5].x(), points[5].y(), points[5].z());
    glVertex3f(points[2].x(), points[2].y(), points[2].z());

    qglColor(Qt::green);
    glVertex3f(points[0].x(), points[0].y(), points[0].z());
    glVertex3f(points[1].x(), points[1].y(), points[1].z());
    glVertex3f(points[6].x(), points[6].y(), points[6].z());
    glVertex3f(points[2].x(), points[2].y(), points[2].z());

    qglColor(Qt::red);
    glVertex3f(points[3].x(), points[3].y(), points[3].z());
    glVertex3f(points[4].x(), points[4].y(), points[4].z());
    glVertex3f(points[7].x(), points[7].y(), points[7].z());
    glVertex3f(points[5].x(), points[5].y(), points[5].z());

    qglColor(Qt::blue);
    glVertex3f(points[5].x(), points[5].y(), points[5].z());
    glVertex3f(points[7].x(), points[7].y(), points[7].z());
    glVertex3f(points[6].x(), points[6].y(), points[6].z());
    glVertex3f(points[2].x(), points[2].y(), points[2].z());

    qglColor(Qt::yellow);
    glVertex3f(points[1].x(), points[1].y(), points[1].z());
    glVertex3f(points[4].x(), points[4].y(), points[4].z());
    glVertex3f(points[7].x(), points[7].y(), points[7].z());
    glVertex3f(points[6].x(), points[6].y(), points[6].z());

    glEnd();
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

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    Quaternion q;

    if (event->key() == Qt::Key_Up) { //вращение по y
        q = Quaternion::qFromAngle(0, 5, 0);
    }
    if (event->key() == Qt::Key_Down) { //вращение по y
        q = Quaternion::qFromAngle(0, -5, 0);
    }
    if (event->key() == Qt::Key_Right) { //вращение по х
        q = Quaternion::qFromAngle(5, 0, 0);
    }
    if (event->key() == Qt::Key_Left) { //вращение по х
        q = Quaternion::qFromAngle(-5, 0, 0);
    }

    for (int i = 0; i < points.size(); i++)
        points[i] = Quaternion::transformVec(q, points[i]);

    updateGL();
}

