#ifndef QUATERNION_H
#define QUATERNION_H

#include <QVector3D>
#include <QQuaternion>

class Quaternion
{
public:
    Quaternion();
    Quaternion(double w, double x, double y, double z);

    Quaternion(QQuaternion & q);

    double getSize();
    void normalize();
    static Quaternion multiply(Quaternion a, Quaternion b);
    static Quaternion multiplyVec(Quaternion a, QVector3D b);
    static QVector3D transformVec(Quaternion q, QVector3D v);
    Quaternion conjugate();
    static Quaternion qFromAngle(double angleX, double angleY, double angleZ);


private:
    double x;
    double y;
    double z;
    double w;
};

#endif // QUATERNION_H
