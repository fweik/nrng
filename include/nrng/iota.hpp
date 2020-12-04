#ifndef NRNG_IOTA_HPP
#define NRNG_IOTA_HPP

#include <numeric>
#include <concepts>
#include <iterator>
#include <ranges>

namespace nrng {

/**
 * @brief Fill a range with increasing values.
 * 
 *  Fills the range [first, last) with sequentially increasing values, 
 *  starting with value and repetitively evaluating ++value.
 *  Behaves like std::iota.
 * 
 * @param first Iterator pointing to the begin of the range.
 * @param last Sentinel limiting the range.
 * @param value Initial value
 * 
 * @return Iterator one past the last element.
 */
template<class T, std::output_iterator<T> O, std::sentinel_for<O> S>
requires std::copyable<T> &&requires(T value)
{
  {
    ++value
  }
  ->std::convertible_to<T>;
}
constexpr O iota(O first, S last, T value)
{
  while (first != last) {
    *first++ = value;
    ++value;
  }

  return first;
}

/**
 * @brief Fill a range with increasing values.
 * 
 *  Fills the range with sequentially increasing values, 
 *  starting with value and repetitively evaluating ++value.
 *  Behaves like std::iota.
 * 
 * @param rng Range to fill.
 * @param value Initial value
 * 
 * @return Iterator one past the last element.
 */
template<class T, std::ranges::output_range<T> R>
constexpr std::ranges::borrowed_iterator_t<R> iota(R &&rng, T value)
{
  using std::begin;
  using std::end;

  return ::nrng::iota(begin(rng), end(rng), value);
}

}// namespace nrng

#endif