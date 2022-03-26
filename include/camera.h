#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "constant.h"
#include "ray.h"
#include "vector.h"

namespace rtiaw {

class Camera {
public:
  Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, FPType vertical_fov,
         FPType aspect_ratio) {
    auto theta = degrees_to_radians(vertical_fov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    auto w = unit_vector(lookfrom - lookat);
    auto u = unit_vector(cross(vup, w));
    auto v = cross(w, u);

    origin = lookfrom;
    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
  }

  Ray get_ray(FPType s, FPType t) const {
    return Ray(origin,
               lower_left_corner + s * horizontal + t * vertical - origin);
  }

private:
  Point3 origin;            // = Point3(0, 0, 0);
  Point3 lower_left_corner; // = origin - horizontal / 2 - vertical / 2 -
                            // Vec3(0, 0, focal_length);
  Vec3 horizontal;          // = Vec3(viewport_width, 0.0, 0.0);
  Vec3 vertical;            // = Vec3(0.0, viewport_height, 0.0);
};

} // namespace rtiaw
#endif // CAMERA_H