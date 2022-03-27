#include "camera.h"
#include "color.h"
#include "common.h"
#include "hittable_list.h"
#include "material.h"
#include "random.h"
#include "sphere.h"

#include <chrono>
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

HittableList random_scene() {
  HittableList world;

  auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
  world.add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = rand_fp();
      Point3 center(a + 0.9 * rand_fp(), 0.2, b + 0.9 * rand_fp());

      if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = Color::random() * Color::random();
          sphere_material = make_shared<Lambertian>(albedo);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = Color::random(0.5, 1);
          auto fuzz = rand_fp(0, 0.5);
          sphere_material = make_shared<Metal>(albedo, fuzz);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<Dielectric>(1.5);
          world.add(make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<Dielectric>(1.5);
  world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
  world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

  return world;
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
  HittableList world = random_scene();

  Point3 lookfrom(13, 2, 3);
  Point3 lookat(0, 0, 0);
  Vec3 vup(0, 1, 0);
  FPType dist_to_focus = 10.0;
  FPType aperture = 0.1;

  Camera cam(lookfrom, lookat, vup, 20, ASPECT_RATIO, aperture, dist_to_focus);

  // Render
  std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

  Image image;

  auto begin = std::chrono::high_resolution_clock::now();

  for (int row = IMAGE_HEIGHT - 1; row >= 0; --row) {
    std::cerr << "\rScanlines remaining: " << row << ' ' << std::flush;

#pragma omp parallel for
    for (int col = 0; col < IMAGE_WIDTH; ++col) {
      Color pixel_color(0, 0, 0);
      for (int s = 0; s < num_samples; ++s) {
        auto u = (static_cast<FPType>(col) + rand_fp()) / (IMAGE_WIDTH - 1);
        auto v = (static_cast<FPType>(row) + rand_fp()) / (IMAGE_HEIGHT - 1);
        Ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      // write_color(std::cout, pixel_color, num_samples);
      image[row][col] = pixel_color;
    }
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  write_color(std::cout, image, num_samples);

  std::cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"
            << std::endl;
  // Finished succesfully
  return 0;
}
