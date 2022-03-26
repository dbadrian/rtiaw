#include "material.h"
#include "hittable.h"

#include <optional>

namespace rtiaw {

std::optional<ScatteredRay> Lambertian::scatter(const Ray &r_in,
                                                const HitRecord &rec) const {
  auto scatter_direction = rec.normal + random_unit_vector();

  // Catch degenerate scatter direction
  if (scatter_direction.near_zero()) {
    scatter_direction = rec.normal;
  }

  return ScatteredRay{.scattered = Ray(rec.p, scatter_direction),
                      .attenuation = albedo};
}

std::optional<ScatteredRay> Metal::scatter(const Ray &r_in,
                                           const HitRecord &rec) const {
  Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
  auto scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
  if (dot(scattered.direction(), rec.normal) < 0) {
    return std::nullopt;
  }

  return ScatteredRay{.scattered = scattered, .attenuation = albedo};
}

} // namespace rtiaw