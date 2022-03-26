#ifndef CONSTANT_H
#define CONSTANT_H

#include <limits>

namespace rtiaw {

using FPPrecision = float;
using FPType = FPPrecision;

constexpr FPType INFINITY = std::numeric_limits<FPType>::infinity();
constexpr FPType PI = 3.1415926535897932385;

// Camera Related
constexpr FPType FOCAL_LENGTH = 1.0;
constexpr FPType ASPECT_RATIO = 16.0 / 9.0;
constexpr static int IMAGE_WIDTH = 720;
constexpr static int IMAGE_HEIGHT =
    static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
const int SAMPLES_PER_PIXEL = 100;

} // namespace rtiaw

#endif // CONSTANT_H