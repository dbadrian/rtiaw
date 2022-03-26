#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "random.h"
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
  // World
  HittableList world;
  world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.5));      // NOLINT
  world.add(make_shared<Sphere>(Point3(0, -100.5, -1), 100)); // NOLINT

  // Camera
  Camera cam;
  // Render

  std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

  for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    for (int i = 0; i < IMAGE_WIDTH; ++i) {
      Color pixel_color(0, 0, 0);
      for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
        auto u = (static_cast<FPType>(i) + rand_fp()) / (IMAGE_WIDTH - 1);
        auto v = (static_cast<FPType>(j) + rand_fp()) / (IMAGE_HEIGHT - 1);
        Ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world);
      }
      write_color(std::cout, pixel_color, SAMPLES_PER_PIXEL);
    }
  }
}
