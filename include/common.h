#ifndef COMMON_H
#define COMMON_H

#include "constant.h"
#include <random>

namespace rtiaw {
// Utility Functions
inline FPType degrees_to_radians(FPType degrees) {
  return degrees * PI / 180.0; // NOLINT
}

inline FPType clamp(FPType x, FPType min, FPType max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

} // namespace rtiaw

#endif // COMMON_H