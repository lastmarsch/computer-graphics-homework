#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QVector3D>
#include <QKeyEvent>
#include <util.h>

class OpenGLWidget : public QGLWidget
{
public:
    OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void cyrusBeck();
    void get_normal_line();
    void drawAxis();
    typedef Vector normal;
    typedef pair<normal, Point> NormalLine;

public slots:
    void drawing(QList<Point> &, double num);

private:
    int number;
    QList<Line> random_line_list;
    QList<Line> clipped_line_list;
    QList<Point> polygon_points;
    QList<NormalLine> polygon_normal_lines;
};

#endif // OPENGLWIDGET_H
