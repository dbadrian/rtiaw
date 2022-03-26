#ifndef Sphere_H
#define Sphere_H

#include "constant.h"
#include "hittable.h"
#include "vector.h"

namespace rtiaw {
class Sphere : public Hittable
{
public:
  Sphere() {}
  Sphere(Point3 center, FPType r) : center(center), radius(r){};

  virtual std::optional<HitRecord> hit(const Ray &r, FPType t_min, FPType t_max) const override;

private:
  Point3 center;
  FPType radius;
};

std::optional<HitRecord> Sphere::hit(const Ray &r, FPType t_min, FPType t_max) const
{
  Vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) return std::nullopt;
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) return std::nullopt;
  }

  auto p = r.at(rec.t);
  auto normal = (rec.p - center) / radius;

  auto vec3 outward_normal = (rec.p - center) / radius;
  auto hrec = HitRecord{ .p = p, .t = root };
  hrec.set_face_normal(r, outward_normal);

  return hrec;
}

}// namespace rtiaw

#endif// Sphere_H