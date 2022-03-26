#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.h"
#include "ray.h"
#include "vector.h"

#include <optional>

namespace rtiaw {
bool inline hit_front_face(const Ray &r, const Vec3 &outward_normal) { return dot(r.direction(), outward_normal) < 0; }

struct HitRecord
{
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;

  inline void set_face_normal(const Ray &r, const Vec3 &outward_normal)
  {
    front_face = hit_front_face(r, outward_normal);
    normal = front_face ? outward_normal : -outward_normal;
  }
};


class Hittable
{
public:
  virtual std::optional<HitRecord> hit(const Ray &r, double t_min, double t_max) const = 0;
};

}// namespace rtiaw

#endif