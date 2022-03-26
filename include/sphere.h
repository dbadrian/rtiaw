#ifndef Sphere_H
#define Sphere_H

#include "constant.h"
#include "hittable.h"
#include "vector.h"

namespace rtiaw {
class Sphere : public Hittable {
public:
  Sphere() = default;
  explicit Sphere(Point3 center, FPType r) : center(center), radius(r){};

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &r, FPType t_min,
                                             FPType t_max) const override;

private:
  Point3 center;
  FPType radius = 1.0;
};

} // namespace rtiaw

#endif // Sphere_H