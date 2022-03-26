#ifndef CONSTANT_H
#define CONSTANT_H

#include <types>

namespace rtiaw {

using FPPrecision = float;
using FPType = FPPrecision;

constexpr FPType INFINITY = std::numeric_limits<FPType>::infinity();
constexpr FPType PI = 3.1415926535897932385;

}// namespace rtiaw

#endif// CONSTANT_H