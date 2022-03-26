#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "random.h"
#include "sphere.h"

#include <iostream>
#include <memory>
#include <span>

using namespace rtiaw;

Color ray_color(const Ray &r, const Hittable &world, int depth) {
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) {
    return Color(0, 0, 0);
  }

  auto rec = world.hit(r, 0.001, INFINITY);
  if (rec) {
    Point3 target = rec->p + rec->normal + random_in_hemisphere();
    return 0.5 * ray_color(Ray(rec->p, target - rec->p), world, depth - 1);
  }
  Vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);                          // NOLINT
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // NOLINT
}

int main(int argc, char *argv[]) {

  const auto args = std::span(argv, static_cast<std::size_t>(argc));

  int num_samples = SAMPLES_PER_PIXEL;
  int max_depth = MAX_SAMPLING_DEPTH;
  if (argc == 3) {
    num_samples = std::stoi(args[1]);
    max_depth = std::stoi(args[2]);
    std::cerr << "Overwrote num_samples=" << num_samples
              << " maxdepth=" << max_depth << std::endl;
  }

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
      for (int s = 0; s < num_samples; ++s) {
        auto u = (static_cast<FPType>(i) + rand_fp()) / (IMAGE_WIDTH - 1);
        auto v = (static_cast<FPType>(j) + rand_fp()) / (IMAGE_HEIGHT - 1);
        Ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      write_color(std::cout, pixel_color, num_samples);
    }
  }

  // Finished succesfully
  return 0;
}
