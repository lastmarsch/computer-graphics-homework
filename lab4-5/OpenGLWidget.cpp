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
}

void OpenGLWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    glViewport(0, 0, w, h);
}

void OpenGLWidget::paintGL()
{
    Vec3f p0(-0.5, -0.8, 0), p1(0.4, 0.5, 0), q0 = p0, q1 = p1;
    cyrusBeck(p0, p1, q0, q1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for(auto& a : points) {
        glVertex2f(a.x, a.y);
    }
    glEnd();  // End of drawing points

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(p0.x, p0.y);
    glVertex2f(p1.x, p1.y);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(q0.x, q0.y);
    glVertex2f(q1.x, q1.y);
    glEnd();

    glFlush();
}

void OpenGLWidget::cyrusBeck(Vec3f p0, Vec3f p1, Vec3f &q0, Vec3f &q1)
{
    Vec3f dir = p1 - p0;
        Vec3f center(0);

        for (auto& a : points) {
            center += a;
        }

        center *= ((GLfloat) 1 / points.size());
        qDebug() << "Center: " << center << "\n";

        for (int i = 0; i < points.size(); i++) {
            Vec3f a0 = points[i];
            Vec3f a1 = points[(i + 1) % points.size()];
            Vec3f adir = a1 - a0;
            Vec3f n;

            if (adir * (a1 - center) == 0) {
                n = a1 - center;
            }
            else {
                GLfloat k = -(adir * (a0 - center)) / (adir * (a1 - center));
                n = (a0 - center) + ((a1 - center) * k);
            }

            if (dir * n != 0) {
                GLfloat t = (a0 - p0).cross(adir) / dir.cross(adir),
                        u = (p0 - a0).cross(dir) / adir.cross(dir);

                qDebug() << "T, U: " << t << ", " << u << "\n";

                if (t <= 1 && t >= 0 && u >= 0 && u <= 1) {
                    qDebug() << "Found!\n";

                    if (dir * n < 0) {
                        q0 = a0 + (adir * u);
                    }
                    else {
                        q1 = a0 + (adir * u);
                    }
                }
                else {
                    qDebug() << "Not found!\n";
                }
            }
            else {
                qDebug() << "Parallel!\n";
            }
        }

        qDebug() << "P0 " << p0 << " P1 " << p1 << " Q0 " << q0 << " Q1 " << q1 << "\n";
}

void OpenGLWidget::drawing(QList<Vec3f>& ps, double num)
{
    points = ps;
    number = num;
    qDebug() << points;
    updateGL();
}



