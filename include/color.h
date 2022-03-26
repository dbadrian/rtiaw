#ifndef COLOR_H
#define COLOR_H

#include "common.h"
#include "vector.h"

#include <iostream>

namespace rtiaw {

constexpr static Vec3::FT COLOR_MAX = 256;

void inline write_color(std::ostream &out, Color pixel_color, // TODO: CONST REF
                        int samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // Divide the color by the number of samples.
  auto scale = 1.0 / samples_per_pixel;
  r *= scale;
  g *= scale;
  b *= scale;

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(COLOR_MAX * clamp(r, 0.0, 0.999)) << ' '
      << static_cast<int>(COLOR_MAX * clamp(g, 0.0, 0.999)) << ' '
      << static_cast<int>(COLOR_MAX * clamp(b, 0.0, 0.999)) << '\n';
}

} // namespace rtiaw

#endif