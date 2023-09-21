#ifndef NRNG_CENTRAL_MOMENT_HPP
#define NRNG_CENTRAL_MOMENT_HPP

#include <nrng/moment.hpp>
#include <nrng/type_traits.hpp>

#include <cmath>

namespace nrng {
/**
 * @brief N-th central moment of range.
 */
template <unsigned Exponent, std::input_iterator I, std::sentinel_for<I> S>
constexpr auto central_moment(I first, S last) {
  auto const mean = ::nrng::mean(first, last);

  return ::nrng::transform_reduce(
             first, last, std::iter_value_t<I>{}, std::plus<>{},
             [mean](auto v) { return power<Exponent>(v - mean); }) /
         std::ranges::distance(first, last);
}

/**
 * @brief N-th central moment of range.
 */
template <unsigned Exponent, std::ranges::input_range Rng>
constexpr auto central_moment(Rng values) {
  return central_moment<Exponent>(std::ranges::begin(values),
                                  std::ranges::end(values));
}

template <std::ranges::input_range Rng> constexpr auto variance(Rng values) {
  return central_moment<2>(values);
}

template <std::input_iterator I, std::sentinel_for<I> S>
constexpr auto variance(I first, S last) {
  return central_moment<2>(first, last);
}

struct sqrt {
  template <class T>
  requires std::is_arithmetic_v<T>
  auto operator()(T const x) const {
    return std::sqrt(x);
  }
};

template <std::input_iterator I, std::sentinel_for<I> S>
requires unary_closed_under<std::iter_value_t<I>, sqrt>
constexpr auto standard_deviation(I first, S last) {
  return sqrt{}(variance(first, last));
}

template <std::ranges::input_range Rng>
requires unary_closed_under<std::ranges::range_value_t<Rng>,
                            sqrt>
constexpr auto standard_deviation(Rng values) {
  return standard_deviation(std::ranges::begin(values),
                            std::ranges::end(values));
}
} // namespace nrng

#endif