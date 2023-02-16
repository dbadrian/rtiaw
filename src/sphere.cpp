#include "sphere.h"

#include <optional>

namespace rtiaw {

std::optional<HitRecord> Sphere::hit(const Ray &r, FPType t_min,
                                     FPType t_max) const {
  Vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) {
    return std::nullopt;
  }
  auto sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range.
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) {
      // see godbolt tune?
      return std::nullopt;
    }
  }

  auto p = r.at(root);
  auto outward_normal = (p - center) / radius;
  auto hrec = HitRecord{
      .p = p,
      .material = material.get(),
      .t = root,
  };
  hrec.set_face_normal(r, outward_normal);

  return hrec;
}

} // namespace rtiaw