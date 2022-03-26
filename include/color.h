#ifndef COLOR_H
#define COLOR_H

#include "vector.h"

#include <iostream>

namespace rtiaw {

constexpr static Vec3::FT COLOR_MAX = 255.999;

void inline write_color_to(std::ostream &out, const Color &pixel_color)
{
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(COLOR_MAX * pixel_color.x()) << ' ' << static_cast<int>(COLOR_MAX * pixel_color.y()) << ' '
      << static_cast<int>(COLOR_MAX * pixel_color.z()) << '\n';
}

}// namespace rtiaw

#endif