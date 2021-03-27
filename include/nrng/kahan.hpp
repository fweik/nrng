#ifndef NRNG_KAHAN_PLUS_HPP
#define NRNG_KAHAN_PLUS_HPP

#include <nrng/accumulate.hpp>
#include <nrng/type_traits.hpp>

#include <concepts>
#include <utility>

namespace nrng {
template <class T> struct kahan_sum_state {
  operator T() const { return sum; }

  T sum;
  T correction;
};

template <std::regular T>
requires binary_closed_under<T, std::plus<>>
    &&binary_closed_under<T, std::minus<>> struct kahan_plus {
  constexpr kahan_sum_state<T> operator()(kahan_sum_state<T> state,
                                          T value) const {
    auto const y = value - state.correction;
    auto const t = state.sum + y;

    return {t, (t - state.sum) - y};
  }
  constexpr kahan_sum_state<T> operator()(T lhs, T rhs) const {
    return (*this)(kahan_sum_state<T>{lhs, {}}, rhs);
  }
};

/**
 * @brief Accumulate range using Kahan summation.
 */
template <class T, std::input_iterator I, std::sentinel_for<I> S>
requires std::convertible_to<std::iter_reference_t<I>, T> constexpr T
kahan_sum(I first, S last, T init) {
  return accumulate(first, last, kahan_sum_state<T>{init, {}}, kahan_plus<T>{})
      .sum;
}

template <class T, std::ranges::input_range Range>
requires std::convertible_to<std::ranges::range_reference_t<Range>,
                             T> constexpr T
kahan_sum(Range rng, T init) {
  return accumulate(rng, kahan_sum_state<T>{init, {}}, kahan_plus<T>{}).sum;
}
} // namespace nrng

#endif