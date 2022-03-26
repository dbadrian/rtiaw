#ifndef RAY_H
#define RAY_H

#include "vector.h"

namespace rtiaw {

class Ray
{
public:
  Ray() = default;
  // TODO(DBA): Strong-typed named arguments?
  Ray(const Point3 &origin, const Vec3 &direction) : orig(origin), dir(direction) {}

  [[nodiscard]] Point3 origin() const { return orig; }
  [[nodiscard]] Vec3 direction() const { return dir; }

  [[nodiscard]] Point3 at(Vec3::FT t) const { return orig + t * dir; }

private:
  Point3 orig;
  Vec3 dir;
};

}// namespace rtiaw

#endif