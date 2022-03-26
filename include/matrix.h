#ifndef MATRIX_H
#define MATRIX_H

#include "constant.h"
#include "vector.h"

#include <array>
#include <cstddef>

namespace rtiaw {

template <class T, std::size_t ROW, std::size_t COL>
using Matrix = std::array<std::array<T, COL>, ROW>;

using Image = Matrix<Color, IMAGE_HEIGHT, IMAGE_WIDTH>;

} // namespace rtiaw

#endif // MATRIX_H