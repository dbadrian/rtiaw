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
         FPType aspect_ratio, FPType aperture, FPType focus_dist) {
    auto theta = degrees_to_radians(vertical_fov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

    lens_radius = aperture / 2;
  }

  Ray get_ray(FPType s, FPType t) const {
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, lower_left_corner + s * horizontal +
                                    t * vertical - origin - offset);
  }

private:
  Point3 origin;
  Point3 lower_left_corner;

  Vec3 horizontal;
  Vec3 vertical;
  Vec3 u, v, w;
  FPType lens_radius;
};

} // namespace rtiaw
#endif // CAMERA_H