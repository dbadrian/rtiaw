#ifndef RANDOM_H
#define RANDOM_H

#include "constant.h"

#include <random>

namespace rtiaw {

// inline uint32_t XOrShift32(uint32_t *state) {
//   uint32_t x = *state;
//   x ^= x << 13;
//   x ^= x >> 17;
//   x ^= x << 5;
//   *state = x;
//   return x;
// }

inline FPType rand_fp() {
  static std::uniform_real_distribution<FPType> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

} // namespace rtiaw

#endif // RANDOM_H