#ifndef UTIL_H
#define UTIL_H

#include <QGLWidget>
#include <math.h>
#include <QDebug>
using namespace std;

class Vector
{
public:
    double x;
    double y;
    double z;
    Vector(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {	}
    void set(const double& _x, const double& _y, const double& _z) { x = _x; y = _y; z = _z; }
    void set(const Vector& v) { x = v.x; y = v.y; z = v.z; }

    friend Vector operator+(const Vector& a, const Vector& b) { return Vector(a.x + b.x, a.y + b.y, a.z + b.z); }
    friend Vector operator-(const Vector & a, const Vector & b) { return Vector(a.x - b.x, a.y - b.y, a.z - b.z); }
    friend Vector operator*(const double& a, const Vector & b) { return Vector(a * b.x, a * b.y, a * b.z); }
    friend Vector cross_product(const Vector & a, const Vector & b)
    {
        return Vector(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
    friend double dot_product(const Vector & a, const Vector & b) { return a.x* b.x + a.y * b.y + a.z * b.z; }
    void normalize()
    {
        double norm = dot_product(*this, *this);
        if (norm <= std::numeric_limits<double>::epsilon())
        {
            return;
        }
        double factor = 1.0 / sqrt(norm);
        x *= factor;
        y *= factor;
        z *= factor;
    }
    friend QDebug operator<< (QDebug out, const Vector &p) {
        return out << p.x << " " << p.y << " " << p.z;
    }
};

class Point
{
public:
    double x;
    double y;
    double z;
    Point(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {}
    void set(const double& _x, const double& _y, const double& _z) { x = _x; y = _y; z = _z; }
    void set(const Point& p) { x = p.x; y = p.y; z = p.z; }

    friend bool operator==(const Point& a, const Point& b)
    {
        return abs(a.x - b.x) < std::numeric_limits<double>::epsilon() && (a.y - b.y) < std::numeric_limits<double>::epsilon();
    }
    // two function below are used linear interpolation
    friend Point operator+(const Point & a, const Point & b) { return Point(a.x + b.x, a.y + b.y, a.z + b.z); }
    friend Point operator*(const double& m, const Point & a) { return Point(m * a.x, m * a.y, m * a.z); }
    friend Vector get_diff(const Point & a, const Point & b)
    {
        return (Vector(a.x - b.x, a.y - b.y, a.z - b.z));
    }
    friend QDebug operator<< (QDebug out, const Point &p) {
       return out << p.x << " " << p.y << " " << p.z;
    }
};

const Point origin;

class Line
{
public:
    Point start;
    Point end;
    Line(const Point& _start = origin, const Point& _end = origin) :start(_start), end(_end)
    {

    }
    void draw_in_gl()const
    {
        glBegin(GL_LINES);
        glVertex2d(start.x, start.y);
        glVertex2d(end.x, end.y);
        glEnd();
    }
    friend QDebug operator<< (QDebug out, const Line &line) {
        return out << "start: " << line.start << "\tend: " << line.end;
    }
};

#endif // UTIL_H
