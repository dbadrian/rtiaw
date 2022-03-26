#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.h"
#include "constant.h"
#include "ray.h"
#include "vector.h"

#include <optional>

namespace rtiaw {

struct HitRecord {
  Point3 p;
  Vec3 normal;
  FPType t;
  bool front_face;

  inline void set_face_normal(const Ray &r, const Vec3 &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  // Hittable(const Hittable &) = default;
  // // Hittable(Hittable &&) = default;
  virtual ~Hittable() = default;
  [[nodiscard]] virtual std::optional<HitRecord> hit(const Ray &r, FPType t_min,
                                                     FPType t_max) const = 0;
};

} // namespace rtiaw

#endif