#ifndef NRNG_TRANSFORM_REDUCE_HPP
#define NRNG_TRANSFORM_REDUCE_HPP

#include <nrng/reduce.hpp>
#include <nrng/type_traits.hpp>

namespace nrng {
template <execution_policy ExecutionPolicy, std::move_constructible T,
          std::forward_iterator I1, std::sentinel_for<I1> S1,
          std::forward_iterator I2, std::sentinel_for<I2> S2, class BinaryOp1,
          class BinaryOp2>
/* clang-format off */
          requires requires(BinaryOp1 op1, BinaryOp2 op2, I1 first1, I2 first2, T init) {
            { op1(init, op2(*first1, *first2)) } -> std::convertible_to<T>;
            { op1(op2(*first1, *first2), init) } -> std::convertible_to<T>;            
            { op1(init, init) } -> std::convertible_to<T>;
            { op1(op2(*first1, *first2), op2(*first1, *first2)) } -> std::convertible_to<T>;
          }
/* clang-format on */
constexpr T transform_reduce(ExecutionPolicy &&policy, I1 first1, S1 last1,
                             I2 first2, S2 last2, T init, BinaryOp1 op1,
                             BinaryOp2 op2) {

  while ((first1 != last1) and (first2 != last2)) {
    init = op1(init, op2(*first1++, *first2++));
  }

  return init;
}

template <std::move_constructible T, std::input_iterator I1,
          std::sentinel_for<I1> S1, std::input_iterator I2,
          std::sentinel_for<I2> S2, class BinaryOp1, class BinaryOp2>
/* clang-format off */
          requires requires(BinaryOp1 op1, BinaryOp2 op2, I1 first1, I2 first2, T init) {
            { op1(init, op2(*first1, *first2)) } -> std::convertible_to<T>;
            { op1(op2(*first1, *first2), init) } -> std::convertible_to<T>;            
            { op1(init, init) } -> std::convertible_to<T>;
            { op1(op2(*first1, *first2), op2(*first1, *first2)) } -> std::convertible_to<T>;
          }
/* clang-format on */
constexpr T transform_reduce(I1 first1, S1 last1, I2 first2, S2 last2, T init,
                             BinaryOp1 op1, BinaryOp2 op2) {
  while ((first1 != last1) and (first2 != last2)) {
    init = op1(init, op2(*first1++, *first2++));
  }

  return init;
}

template <std::move_constructible T, std::ranges::input_range Rng1,
          std::ranges::input_range Rng2, class BinaryOp1, class BinaryOp2>
constexpr T transform_reduce(Rng1 rng1, Rng2 rng2, T init, BinaryOp1 op1,
                             BinaryOp2 op2) {
  using std::ranges::begin;
  using std::ranges::end;

  return ::nrng::transform_reduce(begin(rng1), end(rng1), begin(rng2),
                                  end(rng2), init, op1, op2);
}

template <std::move_constructible T, std::input_iterator I1,
          std::sentinel_for<I1> S1, std::input_iterator I2,
          std::sentinel_for<I2> S2>
/* clang-format off */
          requires requires(I1 first1, I2 first2, T init) {
            { init + (*first1 * *first2) } -> std::convertible_to<T>;
            { (*first1 * *first2) + init } -> std::convertible_to<T>;            
            { init + init } -> std::convertible_to<T>;
            { (*first1 * *first2) + (*first1 * *first2) } -> std::convertible_to<T>;
          }
/* clang-format on */
constexpr T transform_reduce(I1 first1, S1 last1, I2 first2, S2 last2, T init) {
  return ::nrng::transform_reduce(first1, last1, first2, last2, init,
                                  std::plus<>{}, std::multiplies<>{});
}

template <std::move_constructible T, std::ranges::input_range Rng1,
          std::ranges::input_range Rng2>
constexpr T transform_reduce(Rng1 rng1, Rng2 rng2, T init) {
  using std::ranges::begin;
  using std::ranges::end;

  return ::nrng::transform_reduce(begin(rng1), end(rng1), begin(rng2),
                                  end(rng2), init);
}

template <std::move_constructible T, std::input_iterator I,
          std::sentinel_for<I> S, class BinaryOp, class UnaryOp>
constexpr T transform_reduce(I first, S last, T init, BinaryOp binary_op,
                             UnaryOp unary_op) {
  return ::nrng::reduce(first, last, init, [&](auto sum, auto e) {
    return binary_op(sum, unary_op(e));
  });
}

template <std::move_constructible T, std::ranges::input_range Rng,
          class BinaryOp, class UnaryOp>
constexpr T transform_reduce(Rng rng, T init, BinaryOp binary_op,
                             UnaryOp unary_op) {
  return ::nrng::transform_reduce(std::ranges::begin(rng),
                                  std::ranges::end(rng), init, binary_op,
                                  unary_op);
}
} // namespace nrng

#endif