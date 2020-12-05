#ifndef NRNG_TYPE_TRAITS_HPP
#define NRNG_TYPE_TRAITS_HPP

#include <concepts>
#include <type_traits>
#include <execution>

namespace nrng {
/**
 * @brief One of std::execution::{sequenced_policy, parallel_policy, parallel_unsequenced_policy, unsequenced_policy}
 */
template<class T>
concept execution_policy = std::is_execution_policy_v<std::remove_cvref_t<T>>;
}// namespace nrng

#endif