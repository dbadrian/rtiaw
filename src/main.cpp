#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>
#include <memory>

using namespace rtiaw;

Color ray_color(const Ray &r, const Hittable &world) {
  auto rec = world.hit(r, 0, INFINITY);
  if (rec) {
    return 0.5 * (rec->normal + Color(1, 1, 1)); // NOLINT
  }
  Vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);                          // NOLINT
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // NOLINT
}

int main() {

  // Image
  constexpr FPType aspect_ratio = 16.0 / 9.0;
  constexpr static int image_width = 720;
  constexpr static int image_height =
      static_cast<int>(image_width / aspect_ratio);

  // World
  HittableList world;
  world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));      // NOLINT
  world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100)); // NOLINT

  // Camera
  constexpr static FPType viewport_height = 2.0;
  constexpr static FPType viewport_width = aspect_ratio * viewport_height;
  constexpr static FPType focal_length = 1.0;

  auto origin = Point3(0, 0, 0);
  auto horizontal = Vec3(viewport_width, 0, 0);
  auto vertical = Vec3(0, viewport_height, 0);
  auto lower_left_corner =
      origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height - 1; j >= 0; --j) {
    // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    for (int i = 0; i < image_width; ++i) {

      auto u = static_cast<FPType>(i) / (image_width - 1);
      auto v = static_cast<FPType>(j) / (image_height - 1);
      Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      Color pixel_color = ray_color(r, world);

      write_color_to(std::cout, pixel_color);
    }
  }
}
