#ifndef NRNG_REDUCE_HPP
#define NRNG_REDUCE_HPP

#include <nrng/type_traits.hpp>
#include <nrng/accumulate.hpp>

#include <iterator>
#include <algorithm>

namespace nrng {
template<class BinaryOp, class T, class I>
concept ReductionOp = requires(BinaryOp op, T init, I first) {
  /* clang-format off */
  { op(init, *first) } -> std::convertible_to<T>;
  { op(*first, init) } -> std::convertible_to<T>;
  { op(*first, *first) } -> std::convertible_to<T>;
  { op(init, init) } -> std::convertible_to<T>;
  /* clang-format on */
};


/**
 * @brief Reduces the range [first; last), possibly permuted and aggregated in unspecified manner, along with the initial value init over binary_op.
 * 
 * Constrained version of std::reduce, see https://en.cppreference.com/w/cpp/algorithm/reduce.
 */
template<execution_policy ExecutionPolicy, std::forward_iterator I, std::sentinel_for<I> S, std::move_constructible T, ReductionOp<T, I> BinaryOp>
T reduce(ExecutionPolicy &&policy,
  I first,
  S last,
  T init,
  BinaryOp op) {
  return std::reduce(std::forward<ExecutionPolicy>(policy), first, first + std::ranges::distance(first, last), init, op);
}

/** @overload */
template<execution_policy ExecutionPolicy, std::forward_iterator I, std::sentinel_for<I> S, std::move_constructible T>
T reduce(ExecutionPolicy &&policy,
  I first,
  S last,
  T init) {
  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), first, last, init, std::plus<>{});
}

/** @overload */
template<execution_policy ExecutionPolicy, std::forward_iterator I, std::sentinel_for<I> S>
std::iter_value_t<I> reduce(ExecutionPolicy &&policy,
  I first,
  S last) {
  return ::nrng::reduce(std::forward<ExecutionPolicy>(policy), first, last, std::iter_value_t<I>{}, std::plus<>{});
}

/** @overload */
template<std::input_iterator I, std::sentinel_for<I> S, std::move_constructible T, ReductionOp<T, I> BinaryOp>
constexpr std::iter_value_t<I>
  reduce(I first,
    S last,
    T init,
    BinaryOp op) {
  return ::nrng::accumulate(first, last, init, op);
}

/** @overload */
template<std::input_iterator I, std::sentinel_for<I> S, std::move_constructible T>
constexpr std::iter_value_t<I>
  reduce(I first,
    S last,
    T init) {
  return ::nrng::reduce(first, last, init, std::plus<>{});
}

/** @overload */
template<std::input_iterator I, std::sentinel_for<I> S>
constexpr std::iter_value_t<I>
  reduce(
    I first,
    S last) {
  return ::nrng::reduce(first, last, std::iter_value_t<I>{}, std::plus<>{});
}
}// namespace nrng

#endif