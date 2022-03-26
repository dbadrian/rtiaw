#ifndef CAMERA_H
#define CAMERA_H

#include "constant.h"
#include "ray.h"
#include "vector.h"

namespace rtiaw {

class Camera {
public:
  Camera() {
    FPType viewport_height = 2.0;
    FPType viewport_width = ASPECT_RATIO * viewport_height;

    origin = Point3(0, 0, 0);
    horizontal = Vec3(viewport_width, 0.0, 0.0);
    vertical = Vec3(0.0, viewport_height, 0.0);
    lower_left_corner =
        origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, FOCAL_LENGTH);
  }

  Ray get_ray(double u, double v) const {
    return Ray(origin,
               lower_left_corner + u * horizontal + v * vertical - origin);
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