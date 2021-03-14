#ifndef NRNG_POWER_HPP
#define NRNG_POWER_HPP

namespace nrng {
template <unsigned Exponent, class T> constexpr T power(T x) {
  if constexpr (Exponent == 0) {
    return T{1};
  } else {
    if constexpr (Exponent % 2 == 0) {
      auto const square = power<Exponent - 1>(x);
      return square * square;
    } else {
      return x * power<Exponent - 1>(x);
    }
  }
}
} // namespace nrng

#endif