#ifndef NRNG_MOMENT_HPP
#define NRNG_MOMENT_HPP

#include <concepts>
#include <iterator>

#include <nrng/power.hpp>
#include <nrng/transform_reduce.hpp>

namespace nrng {

/**
 * @brief N-th (raw) moment of range.
 */
template <unsigned Exponent, std::input_iterator I, std::sentinel_for<I> S>
constexpr auto moment(I first, S last) {
  return ::nrng::transform_reduce(first, last, std::iter_value_t<I>{},
                                  std::plus<>{},
                                  [](auto v) { return power<Exponent>(v); }) /
         std::ranges::distance(first, last);
}

/**
 * @brief N-th (raw) moment of range.
 */
template <unsigned Exponent, std::ranges::input_range Rng>
constexpr auto moment(Rng values) {
  return moment<Exponent>(std::ranges::begin(values), std::ranges::end(values));
}

template <std::input_iterator I, std::sentinel_for<I> S>
constexpr auto mean(I first, S last) {
  return moment<1>(first, last);
}

template <std::ranges::input_range Rng> constexpr auto mean(Rng rng) {
  return moment<1>(std::ranges::begin(rng), std::ranges::end(rng));
}
} // namespace nrng

#endif