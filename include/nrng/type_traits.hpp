#ifndef NRNG_TYPE_TRAITS_HPP
#define NRNG_TYPE_TRAITS_HPP

#include <concepts>
#include <execution>
#include <type_traits>

namespace nrng {
/**
 * @brief One of std::execution::{sequenced_policy, parallel_policy,
 * parallel_unsequenced_policy, unsequenced_policy}
 */
template <class T>
concept execution_policy = std::is_execution_policy_v<std::remove_cvref_t<T>>;

/** @brief BinaryOp: T x T -> T. */
template <class T, class BinaryOp>
concept binary_closed_under = requires(BinaryOp op, T t) {
  { op(t, t) } -> std::convertible_to<T>;
};

/** @brief UnaryOp: T -> T. */
template <class T, class UnaryOp>
concept unary_closed_under = requires(UnaryOp op, T t) {
  { op(t) } -> std::convertible_to<T>;
};
} // namespace nrng

#endif