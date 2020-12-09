#ifndef NRNG_ADJACENT_DIFFERENCE_HPP
#define NRNG_ADJACENT_DIFFERENCE_HPP

#include <nrng/type_traits.hpp>

#include <functional>
#include <algorithm>
#include <concepts>
#include <numeric>

namespace nrng {
template<execution_policy ExecutionPolicy, std::forward_iterator I, std::sentinel_for<I> S, std::output_iterator<std::iter_value_t<I>> O, class BinaryOp>
requires binary_closed_under<std::iter_value_t<I>, BinaryOp> && std::forward_iterator<O>
constexpr std::ranges::in_out_result<I, O> adjacent_difference(ExecutionPolicy &&policy, I first, S last, O out, BinaryOp op)
{
  auto last_it = first + std::ranges::distance(first, last);

  return { std::move(last_it), std::adjacent_difference(policy, first, last_it, out, op) };
}

template<execution_policy ExecutionPolicy, std::forward_iterator I, std::sentinel_for<I> S, std::output_iterator<std::iter_value_t<I>> O>
requires binary_closed_under<std::iter_value_t<I>, std::minus<>> constexpr std::ranges::in_out_result<I, O> adjacent_difference(ExecutionPolicy &&policy, I first, S last, O out)
{
  return ::nrng::adjacent_difference(std::forward<ExecutionPolicy>(policy), first, last, out, std::minus<>{});
}

template<std::forward_iterator I, std::sentinel_for<I> S, std::output_iterator<std::iter_value_t<I>> O, class BinaryOp>
requires binary_closed_under<std::iter_value_t<I>, BinaryOp> constexpr std::ranges::in_out_result<I, O> adjacent_difference(I first, S last, O out, BinaryOp op)
{
  if (first == last) {
    return { std::move(first), std::move(out) };
  }

  /* The first element is just copied */
  *out++ = *first;
  /* The rest can be mapped to transform. */
  auto res = std::ranges::transform(first + 1, last, first, last, out, op);

  return { std::move(res.in1), std::move(res.out) };
}

template<std::input_iterator I, std::sentinel_for<I> S, std::output_iterator<std::iter_value_t<I>> O, class BinaryOp>
requires binary_closed_under<std::iter_value_t<I>, BinaryOp> constexpr std::ranges::in_out_result<I, O> adjacent_difference(I first, S last, O out, BinaryOp op)
{
  if (first == last)
    return { std::move(first), std::move(out) };

  auto acc = *first;
  *out = acc;
  while (++first != last) {
    auto val = *first;
    *++out = op(val, std::move(acc));
    acc = std::move(val);
  }
  return { std::move(first), std::move(++out) };
}

template<std::input_iterator I, std::sentinel_for<I> S, std::output_iterator<std::iter_value_t<I>> O>
requires binary_closed_under<std::iter_value_t<I>, std::minus<>> 
constexpr std::ranges::in_out_result<I, O> adjacent_difference(I first, S last, O out)
{
  return ::nrng::adjacent_difference(first, last, out, std::minus<>{});
}

template<std::ranges::input_range Rng, std::output_iterator<std::ranges::range_value_t<Rng>> O>
requires binary_closed_under<std::ranges::range_value_t<Rng>, std::minus<>> constexpr std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Rng>, O> adjacent_difference(Rng &&rng, O out)
{
  using std::ranges::begin;
  using std::ranges::end;

  return ::nrng::adjacent_difference(begin(rng), end(rng), out);
}

template<std::ranges::input_range Rng, std::output_iterator<std::ranges::range_value_t<Rng>> O, class BinaryOp>
requires binary_closed_under<std::ranges::range_value_t<Rng>, BinaryOp> constexpr std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Rng>, O> adjacent_difference(Rng &&rng, O out, BinaryOp op)
{
  using std::ranges::begin;
  using std::ranges::end;

  return ::nrng::adjacent_difference(begin(rng), end(rng), out, op);
}

template<execution_policy ExecutionPolicy, std::ranges::forward_range Rng, std::output_iterator<std::ranges::range_value_t<Rng>> O>
requires binary_closed_under<std::ranges::range_value_t<Rng>, std::minus<>> constexpr std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Rng>, O> adjacent_difference(ExecutionPolicy &&policy, Rng &&rng, O out)
{
  using std::ranges::begin;
  using std::ranges::end;

  return ::nrng::adjacent_difference(std::forward<ExecutionPolicy>(policy), begin(rng), end(rng), out);
}

template<execution_policy ExecutionPolicy, std::ranges::forward_range Rng, std::output_iterator<std::ranges::range_value_t<Rng>> O, class BinaryOp>
requires binary_closed_under<std::ranges::range_value_t<Rng>, BinaryOp> constexpr std::ranges::in_out_result<std::ranges::borrowed_iterator_t<Rng>, O> adjacent_difference(ExecutionPolicy &&policy, Rng &&rng, O out, BinaryOp op)
{
  using std::ranges::begin;
  using std::ranges::end;

  return ::nrng::adjacent_difference(std::forward<ExecutionPolicy>(policy), begin(rng), end(rng), out, op);
}
}// namespace nrng
#endif