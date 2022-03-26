#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vector.h"

#include <optional>

namespace rtiaw {

struct HitRecord;

struct ScatteredRay {
  Ray scattered;
  Color attenuation;
};

class Material {
public:
  virtual ~Material() = default;
  [[nodiscard]] virtual std::optional<ScatteredRay>
  scatter(const Ray &r_in, const HitRecord &rec) const = 0;
};

class Lambertian : public Material {
public:
  Lambertian(const Color &a) : albedo(a) {}

  [[nodiscard]] std::optional<ScatteredRay>
  scatter(const Ray &r_in, const HitRecord &rec) const override;
  //   {
  //     auto scatter_direction = rec.normal + random_unit_vector();

  //     // Catch degenerate scatter direction
  //     if (scatter_direction.near_zero()) {
  //       scatter_direction = rec.normal;
  //     }

  //     return ScatteredRay{.scattered = Ray(rec.p, scatter_direction),
  //                         .attenuation = albedo};
  //   }

private:
  Color albedo;
};

class Metal : public Material {
public:
  Metal() = delete;
  explicit Metal(const Color &a, FPType f) : albedo(a), fuzz(f < 1 ? f : 1) {}

  [[nodiscard]] std::optional<ScatteredRay>
  scatter(const Ray &r_in, const HitRecord &rec) const override;
  //    {
  //     Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
  //     auto scattered = Ray(rec.p, reflected);
  //     if (dot(scattered.direction(), rec.normal) < 0) {
  //       return std::nullopt;
  //     }

  //     return ScatteredRay{.scattered = scattered, .attenuation = albedo};
  //   }

public:
  Color albedo;
  FPType fuzz;
};

class Dielectric : public Material {
public:
  Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

  [[nodiscard]] std::optional<ScatteredRay>
  scatter(const Ray &r_in, const HitRecord &rec) const override;

private:
  double ir; // Index of Refraction
};

} // namespace rtiaw

#endif // MATERIAL_H