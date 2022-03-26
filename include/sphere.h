#ifndef Sphere_H
#define Sphere_H

#include "constant.h"
#include "hittable.h"
#include "vector.h"

#include <memory>

namespace rtiaw {

class Sphere : public Hittable {
public:
  Sphere() = default;
  explicit Sphere(Point3 center, FPType r, std::shared_ptr<Material> material)
      : center(center), radius(r), material(material){};

  [[nodiscard]] std::optional<HitRecord> hit(const Ray &r, FPType t_min,
                                             FPType t_max) const override;

private:
  Point3 center;
  FPType radius = 1.0;
  std::shared_ptr<Material> material;
};

} // namespace rtiaw

#endif // Sphere_H