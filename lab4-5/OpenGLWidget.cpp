#include "OpenGLWidget.h"
#include <QDebug>
#include <math.h>
#include <random>
#include <ctime>


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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    drawAxis();

    glLineWidth(2);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for(auto& a : polygon_points) {
        glVertex2f(a.x, a.y);
    }
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3d(0, 0, 0);
    if (!polygon_points.isEmpty()) {
        Point p = polygon_points.last();
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3d(1, 0, 0);
    for (auto& x : random_line_list)
    {
        x.draw_in_gl();
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3d(0, 1, 0);
    for (auto& x : clipped_line_list)
    {
        x.draw_in_gl();
    }
    glEnd();

    glFlush();

    random_line_list.clear();
    clipped_line_list.clear();
}

void OpenGLWidget::drawAxis()
{
    glLineWidth(3.0f); // устанавливаем ширину линии

    glColor3d(0.8, 0.8, 0.8); // устанавливается цвет последующих линий
    // ось x
    glBegin(GL_LINES); // построение линии
    glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
    glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
    glEnd();

    glColor3d(0.8, 0.8, 0.8);
    glBegin(GL_LINES);
    // ось y
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 0.0f, -1.0f,  0.0f);
    glEnd();
}

void OpenGLWidget::get_normal_line()
{
    int length = polygon_points.size();
    for (int i = 0; i < length; i++)
    {
        const Point& a = polygon_points[i];
        const Point& b = polygon_points[(i + 1) % length];
        const Point& c = polygon_points[(i + 2) % length];
        Vector direction1(b.x - a.x, b.y - a.y);
        Vector direction2(c.x - b.x, c.y - b.y);
        Vector n = cross_product(direction1, cross_product(direction1, direction2));
        n.z = 0;
        polygon_normal_lines.push_back(make_pair(n, a));
    }
    qDebug() << polygon_normal_lines;
}

void OpenGLWidget::cyrusBeck()
{
    for (auto& line : random_line_list)
    {
        Vector direction(line.end.x - line.start.x, line.end.y - line.start.y);
        double t_in = 0;
        double t_out = 1;
        double numer;
        double denom;
        int in_poly = 1;
        for (auto& normal_line : polygon_normal_lines)
        {
            const auto& p = normal_line.second;
            const auto& n = normal_line.first;

            denom = dot_product(direction, n);
            numer = dot_product(Vector(p.x - line.start.x, p.y - line.start.y), n);

            if (denom < 0)
            {
                t_in = max(t_in, numer / denom);
            }
            else
            {
                t_out = min(t_out, numer / denom);
            }
            if (t_in > t_out)
            {
                in_poly = 0;
                break;
            }
        }
        if (in_poly)
        {
            clipped_line_list.push_back(Line(
                                            Point(line.start.x + (line.end.x - line.start.x) * t_in, line.start.y + (line.end.y - line.start.y ) * t_in),
                                            Point(line.start.x + (line.end.x - line.start.x) * t_out, line.start.y + (line.end.y - line.start.y) * t_out)
                                            ));
        }
    }
}

void OpenGLWidget::drawing(QList<Point> &ps, double num)
{
    random_line_list.clear();
    polygon_points.clear();
    polygon_normal_lines.clear();
    clipped_line_list.clear();

    polygon_points = ps;
    number = num;

    std::mt19937 rng(time(0));
    std::uniform_real_distribution<> dist(-1, 1);
    for (int i = 0; i < this->number; i++) {
        Point p0(dist(rng), dist(rng)),
                p1(dist(rng), dist(rng));
        random_line_list.append(Line(p0, p1));
    }

    get_normal_line();
    cyrusBeck();
    updateGL();
}




