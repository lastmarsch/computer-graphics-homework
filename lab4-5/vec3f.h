#ifndef VEC3F_H
#define VEC3F_H
#include <QDebug>

template<typename T>
struct Vec3 {
    T x, y, z;

    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(T x) : x(x), y(x), z(x) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vec3& normalize() {
        T nor2 = dot(*this);

        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }

        return *this;
    }
    Vec3<T> operator * (const T& f) const {
        return Vec3<T>(x * f, y * f, z * f);
    }
    T operator * (const Vec3<T>& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    T cross(const Vec3<T>& v) const {
        return x * v.y - y * v.x;
    }
    Vec3<T> operator - (const Vec3<T>& v) const {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    Vec3<T> operator + (const Vec3<T>& v) const {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vec3<T>& operator += (const Vec3<T>& v) {
        x += v.x, y += v.y, z += v.z;

        return *this;
    }
    Vec3<T>& operator *= (const Vec3<T>& v) {
        x *= v.x, y *= v.y, z *= v.z;

        return *this;
    }
    Vec3<T> operator - () const {
        return Vec3<T>(-x, -y, -z);
    }
    T length() const {
        return sqrt(x * x + y * y + z * z);
    }

    friend QDebug operator<< (QDebug d, const Vec3 &v) {
        d << "[ X = " << v.x << ", Y = " << v.y << ", Z = " << v.z << " ]";
        return d;
    }
};

#endif // VEC3F_H
