#ifndef Vector3_H
#define Vector3_H

#include "constant.h"

#include <cmath>
#include <concepts>
#include <iostream>


using std::sqrt;

namespace rtiaw {

template<std::floating_point T> class Vector3
{
public:
  using FT = T;

  Vector3() : e{ 0, 0, 0 } {}
  Vector3(T e0, T e1, T e2) : e{ e0, e1, e2 } {}

  [[nodiscard]] T x() const { return e[0]; }
  [[nodiscard]] T y() const { return e[1]; }
  [[nodiscard]] T z() const { return e[2]; }

  Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
  [[nodiscard]] T operator[](int i) const { return e[i]; }
  [[nodiscard]] T &operator[](int i) { return e[i]; }

  Vector3 &operator+=(const Vector3 &v)
  {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  Vector3 &operator*=(const T t)
  {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  Vector3 &operator/=(const T t) { return *this *= 1 / t; }

  [[nodiscard]] T length() const { return sqrt(length_squared()); }

  [[nodiscard]] T length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

public:
  T e[3];
};

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

using Vec3 = Vector3<FPPrecision>;

// Type aliases for Vector3
using Point3 = Vec3;// 3D point
using Color = Vec3;// RGB color


template<typename T> inline std::ostream &operator<<(std::ostream &out, const Vector3<T> &v)
{
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

template<typename T> inline Vector3<T> operator+(const Vector3<T> &u, const Vector3<T> &v)
{
  return Vector3<T>(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

template<typename T> inline Vector3<T> operator-(const Vector3<T> &u, const Vector3<T> &v)
{
  return Vector3<T>(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

template<typename T> inline Vector3<T> operator*(const Vector3<T> &u, const Vector3<T> &v)
{
  return Vector3<T>(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

template<typename T> inline Vector3<T> operator*(double t, const Vector3<T> &v)
{
  return Vector3<T>(t * v.e[0], t * v.e[1], t * v.e[2]);
}

template<typename T> inline Vector3<T> operator*(const Vector3<T> &v, double t) { return t * v; }

template<typename T> inline Vector3<T> operator/(Vector3<T> v, double t) { return (1 / t) * v; }

template<typename T> inline double dot(const Vector3<T> &u, const Vector3<T> &v)
{
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

template<typename T> inline Vector3<T> cross(const Vector3<T> &u, const Vector3<T> &v)
{
  return Vector3<T>(
    u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

template<typename T> inline Vector3<T> unit_vector(Vector3<T> v) { return v / v.length(); }

}// namespace rtiaw


#endif