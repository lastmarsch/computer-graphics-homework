#include "quaternion.h"
#include <math.h>
Quaternion::Quaternion()
{

}

Quaternion::Quaternion(double w, double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(QQuaternion &q)
{
    this->x = q.x();
    this->y = q.y();
    this->z = q.z();
    this->w = q.scalar();
}

double Quaternion::getSize()
{
    return sqrt(w * w + x * x + y * y + z * z);
}

void Quaternion::normalize()
{
    double sizeInv = 1 / getSize();
    x *= sizeInv;
    y *= sizeInv;
    z *= sizeInv;
    w *= sizeInv;
}

Quaternion Quaternion::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

Quaternion Quaternion::qFromAngle(double angleX, double angleY, double angleZ)
{
    Quaternion X(cos(angleX / 2), 0, sin(angleX / 2), 0);
    Quaternion Y(cos(angleY / 2), sin(angleY / 2), 0, 0);
    Quaternion Z(cos(angleZ / 2), 0, 0, sin(angleZ / 2));

    Quaternion tmp = multiply(Z, Y);
    return multiply(tmp, X);
}

Quaternion Quaternion::multiply(Quaternion a, Quaternion b)
{
    Quaternion tmp;
    tmp.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    tmp.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    tmp.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    tmp.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    return tmp;
}

Quaternion Quaternion::multiplyVec(Quaternion a, QVector3D b)
{
    Quaternion tmp;
    tmp.w = -a.x * b.x() - a.y * b.y() - a.z * b.z();
    tmp.x = a.w * b.x() + a.y * b.z() - a.z * b.y();
    tmp.y = a.w * b.y() - a.x * b.z() + a.z * b.x();
    tmp.z = a.w * b.z() + a.x * b.y() - a.y * b.x();
    return tmp;
}

QVector3D Quaternion::transformVec(Quaternion q, QVector3D v)
{
    Quaternion tmp;
    tmp = multiplyVec(q, v);

    tmp = multiply(tmp, q.conjugate());
    return QVector3D(tmp.x, tmp.y, tmp.z);
}
