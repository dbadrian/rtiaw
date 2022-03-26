#ifndef Vector3_H
#define Vector3_H

#include "constant.h"
#include "random.h"

#include <array>
#include <cmath>
#include <concepts>
#include <iostream>

using std::sqrt;

namespace rtiaw {

template <std::floating_point T> class Vector3 {
public:
  using FT = T;

  Vector3() : e{0, 0, 0} {}
  Vector3(T e0, T e1, T e2) : e{e0, e1, e2} {}

  [[nodiscard]] T x() const { return e[0]; }
  [[nodiscard]] T y() const { return e[1]; }
  [[nodiscard]] T z() const { return e[2]; }

  Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
  [[nodiscard]] T operator[](std::size_t i) const { return e[i]; }
  [[nodiscard]] T &operator[](std::size_t i) { return e[i]; }

  Vector3 &operator+=(const Vector3 &v) {
    e[0] += v[0];
    e[1] += v[1];
    e[2] += v[2];
    return *this;
  }

  Vector3 &operator*=(const T t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  Vector3 &operator/=(const T t) { return *this *= 1 / t; }

  [[nodiscard]] T length() const { return sqrt(length_squared()); }

  [[nodiscard]] T length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  [[nodiscard]] inline static Vector3 random() {
    return Vector3(rand_fp(), rand_fp(), rand_fp());
  }

  [[nodiscard]] inline static Vector3 random(FPType min, FPType max) {
    return Vector3(rand_fp(min, max), rand_fp(min, max), rand_fp(min, max));
  }

private:
  std::array<T, 3> e;
};

using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

using Vec3 = Vector3<FPPrecision>;

// Type aliases for Vector3
using Point3 = Vec3; // 3D point
using Color = Vec3;  // RGB color

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const Vector3<T> &v) {
  return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

template <typename T>
inline Vector3<T> operator+(const Vector3<T> &u, const Vector3<T> &v) {
  return Vector3<T>(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T> &u, const Vector3<T> &v) {
  return Vector3<T>(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

template <typename T>
inline Vector3<T> operator*(const Vector3<T> &u, const Vector3<T> &v) {
  return Vector3<T>(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

template <typename T>
inline Vector3<T> operator*(FPType t, const Vector3<T> &v) {
  return Vector3<T>(t * v[0], t * v[1], t * v[2]);
}

template <typename T>
inline Vector3<T> operator*(const Vector3<T> &v, FPType t) {
  return t * v;
}

template <typename T> inline Vector3<T> operator/(Vector3<T> v, FPType t) {
  return (1 / t) * v;
}

template <typename T>
inline FPType dot(const Vector3<T> &u, const Vector3<T> &v) {
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &u, const Vector3<T> &v) {
  return Vector3<T>(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2],
                    u[0] * v[1] - u[1] * v[0]);
}

template <typename T> inline Vector3<T> unit_vector(Vector3<T> v) {
  return v / v.length();
}

inline Vec3 random_in_unit_sphere() {
  while (true) {
    auto p = Vec3::random(-1.0, 1.0);
    if (p.length_squared() >= 1) {
      continue;
    }
    return p;
  }
}

inline Vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_in_hemisphere(const Vec3 &normal) {
  auto in_unit_sphere = random_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return in_unit_sphere;
  else
    return -in_unit_sphere;
}

} // namespace rtiaw

#endif