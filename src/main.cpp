#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
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
    auto ray = rec->material->scatter(r, rec.value());
    if (ray) {
      return ray->attenuation * ray_color(ray->scattered, world, depth - 1);
    }
    return Color(0, 0, 0);
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

  auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
  auto material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
  auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

  world.add(
      make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
  world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

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
