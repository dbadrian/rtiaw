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

std::optional<ScatteredRay> Dielectric::scatter(const Ray &r_in,
                                                const HitRecord &rec) const {
  FPType refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

  auto unit_direction = unit_vector(r_in.direction());

  FPType cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
  FPType sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  Vec3 direction;
  bool cannot_refract = refraction_ratio * sin_theta > 1.0;
  if (cannot_refract) {
    direction = reflect(unit_direction, rec.normal);
  } else {
    direction = refract(unit_direction, rec.normal, refraction_ratio);
  }

  return ScatteredRay{.scattered = Ray(rec.p, direction),
                      .attenuation = Color(1.0, 1.0, 1.0)};
}

} // namespace rtiaw