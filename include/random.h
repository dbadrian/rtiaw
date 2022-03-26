// inline uint32_t XOrShift32(uint32_t *state)
// {
//   uint32_t x = *state;
//   x ^= x << 13;
//   x ^= x >> 17;
//   x ^= x << 5;
//   *state = x;
//   return x;
// }