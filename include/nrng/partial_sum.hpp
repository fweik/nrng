#ifndef NRNG_IOTA_HPP
#define NRNG_IOTA_HPP

#include <concepts>

#include <nrng/type_traits.hpp>

namespace nrng {
template <std::input_iterator I, std::sentinel_for<I> S,
          std::output_iterator<std::iter_value_t<I>> O,
          std::invocable<std::iter_value_t<I>, std::iter_value_t<I>> BinaryOp>
requires std::convertible_to<
    std::invoke_result_t<BinaryOp, std::iter_value_t<I>, std::iter_value_t<I>>,
    std::iter_value_t<I>> constexpr O
partial_sum(I first, S last, O d_first, BinaryOp op) {
  if (first == last)
    return d_first;

  auto sum = *first;
  *d_first = sum;

  while (++first != last) {
    sum = op(std::move(sum), *first);
    *++d_first = sum;
  }
  return ++d_first;
}

template <std::ranges::input_range Rng,
          std::output_iterator<std::ranges::range_value_t<Rng>> O,
          std::invocable<std::ranges::range_value_t<Rng>,
                         std::ranges::range_value_t<Rng>>
              BinaryOp>
constexpr O partial_sum(Rng rng, O d_first, BinaryOp op) {
  return partial_sum(std::ranges::begin(rng), std::ranges::end(rng), d_first,
                     op);
}

template <std::ranges::input_range Rng,
          std::ranges::output_range<std::ranges::range_value_t<Rng>> ORng,
          std::invocable<std::ranges::range_value_t<Rng>,
                         std::ranges::range_value_t<Rng>>
              BinaryOp>
constexpr std::ranges::borrowed_iterator_t<ORng>
partial_sum(Rng rng, ORng &&out, BinaryOp op) {
  return partial_sum(std::ranges::begin(rng), std::ranges::end(rng),
                     std::ranges::begin(out), op);
}

template <std::input_iterator I, std::sentinel_for<I> S,
          std::output_iterator<std::iter_value_t<I>> O>
requires std::convertible_to<
    std::invoke_result_t<std::plus<>, std::iter_value_t<I>,
                         std::iter_value_t<I>>,
    std::iter_value_t<I>> constexpr O
partial_sum(I first, S last, O d_first) {
  return partial_sum(first, last, d_first, std::plus<>{});
}

template <std::ranges::input_range Rng,
          std::output_iterator<std::ranges::range_value_t<Rng>> O>
constexpr O partial_sum(Rng rng, O d_first) {
  return partial_sum(std::ranges::begin(rng), std::ranges::end(rng), d_first,
                     std::plus<>{});
}

template <std::ranges::input_range Rng,
          std::ranges::output_range<std::ranges::range_value_t<Rng>> ORng>
constexpr std::ranges::borrowed_iterator_t<ORng> partial_sum(Rng in,
                                                             ORng &&out) {
  return partial_sum(std::ranges::begin(in), std::ranges::end(in),
                     std::ranges::begin(out), std::plus<>{});
}
} // namespace nrng

#endif