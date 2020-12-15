#ifndef NRNG_REDUCE_HPP
#define NRNG_REDUCE_HPP

#include <nrng/accumulate.hpp>
#include <nrng/type_traits.hpp>

#include <algorithm>
#include <functional>
#include <iterator>

namespace nrng {
template <class BinaryOp, class T, class I>
concept ReductionOp = requires(BinaryOp op, T init, I first) {
  /* clang-format off */
  { op(init, *first) } -> std::convertible_to<T>;
  { op(*first, init) } -> std::convertible_to<T>;
  { op(*first, *first) } -> std::convertible_to<T>;
  { op(init, init) } -> std::convertible_to<T>;
  /* clang-format on */
};

/**
 * @brief Reduces the range [first; last), possibly permuted and aggregated in
 * unspecified manner, along with the initial value init over binary_op.
 *
 * Constrained version of std::reduce, see
 * https://en.cppreference.com/w/cpp/algorithm/reduce.
 */
template <execution_policy ExecutionPolicy, std::forward_iterator I,
          std::sentinel_for<I> S, std::move_constructible T,
          ReductionOp<T, I> BinaryOp>
T reduce(ExecutionPolicy &&policy, I first, S last, T init, BinaryOp op) {
  if constexpr (std::is_same_v<I, S>) {
    return std::reduce(std::forward<ExecutionPolicy>(policy), first, last, init,
                       op);
  } else {
    return std::reduce(std::forward<ExecutionPolicy>(policy), first,
                       std::next(first, std::ranges::distance(first, last)),
                       init, op);
  }
}

/** @overload */
template <execution_policy ExecutionPolicy, std::ranges::forward_range Rng,
          std::move_constructible T,
          ReductionOp<T, std::ranges::iterator_t<Rng>> BinaryOp>
T reduce(ExecutionPolicy &&policy, Rng rng, T init, BinaryOp op) {
  using std::begin;
  using std::end;

  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), begin(rng),
                        end(rng), init, op);
}

/** @overload */
template <execution_policy ExecutionPolicy, std::forward_iterator I,
          std::sentinel_for<I> S, std::move_constructible T>
T reduce(ExecutionPolicy &&policy, I first, S last, T init) {
  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), first, last,
                        init, std::plus<>{});
}

/** @overload */
template <execution_policy ExecutionPolicy, std::ranges::forward_range Rng,
          std::move_constructible T>
T reduce(ExecutionPolicy &&policy, Rng rng, T init) {
  using std::begin;
  using std::end;

  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), begin(rng),
                        end(rng), init, std::plus<>{});
}

/** @overload */
template <execution_policy ExecutionPolicy, std::forward_iterator I,
          std::sentinel_for<I> S>
std::iter_value_t<I> reduce(ExecutionPolicy &&policy, I first, S last) {
  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), first, last,
                        std::iter_value_t<I>{}, std::plus<>{});
}

/** @overload */
template <execution_policy ExecutionPolicy, std::ranges::forward_range Rng>
std::ranges::range_value_t<Rng> reduce(ExecutionPolicy &&policy, Rng rng) {
  using std::begin;
  using std::end;

  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), begin(rng),
                        end(rng), std::ranges::range_value_t<Rng>{},
                        std::plus<>{});
}

/** @overload */
template <std::input_iterator I, std::sentinel_for<I> S,
          std::move_constructible T, ReductionOp<T, I> BinaryOp>
constexpr T reduce(I first, S last, T init, BinaryOp op) {
  return ::nrng::accumulate(first, last, init, op);
}

/** @overload */
template <std::ranges::forward_range Rng, std::move_constructible T,
          ReductionOp<T, std::ranges::iterator_t<Rng>> BinaryOp>
constexpr T reduce(Rng rng, T init, BinaryOp op) {
  return ::nrng::accumulate(rng, init, op);
}

/** @overload */
template <std::input_iterator I, std::sentinel_for<I> S,
          std::move_constructible T>
constexpr std::iter_value_t<I> reduce(I first, S last, T init) {
  return ::nrng::reduce(first, last, init, std::plus<>{});
}

/** @overload */
template <std::ranges::forward_range Rng, std::move_constructible T>
constexpr std::ranges::range_value_t<Rng> reduce(Rng rng, T init) {
  return ::nrng::accumulate(rng, init, std::plus<>{});
}

/** @overload */
template <std::input_iterator I, std::sentinel_for<I> S>
constexpr std::iter_value_t<I> reduce(I first, S last) {
  return ::nrng::reduce(first, last, std::iter_value_t<I>{}, std::plus<>{});
}

/** @overload */
template <std::ranges::forward_range Rng>
constexpr std::ranges::range_value_t<Rng> reduce(Rng rng) {
  return ::nrng::accumulate(rng, std::ranges::range_value_t<Rng>{},
                            std::plus<>{});
}
} // namespace nrng

#endif