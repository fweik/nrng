#ifndef NRNG_ACCUMULATE_HPP
#define NRNG_ACCUMULATE_HPP

#include <numeric>
#include <concepts>
#include <ranges>
#include <iterator>
#include <functional>

namespace nrng {
template<class T, std::input_iterator I, std::sentinel_for<I> S, std::invocable<T, std::iter_reference_t<I>> BinaryOp>
requires requires(T t, I i, BinaryOp op)
{
  { t = op(std::move(t), *i) };
}
constexpr T accumulate(I first, S last, T init, BinaryOp op)
{
  for (; first != last; ++first) {
    init = op(std::move(init), *first);
  }

  return init;
}

template<class T, std::input_iterator I, std::sentinel_for<I> S>
constexpr T accumulate(I first, S last, T init)
{
  return ::nrng::accumulate(first, last, init, std::plus<>{});
}

template<class T, std::ranges::input_range Rng>
constexpr T accumulate(Rng rng, T init)
{
  using std::begin;
  using std::end;

  return ::nrng::accumulate(begin(rng), end(rng), init, std::plus<>{});
}

template<class T, std::ranges::input_range Rng, std::invocable<T, std::ranges::range_reference_t<Rng>> BinaryOp>
constexpr T accumulate(Rng rng, T init, BinaryOp op)
{
  using std::begin;
  using std::end;

  return ::nrng::accumulate(begin(rng), end(rng), init, op);
}
}// namespace nrng

#endif