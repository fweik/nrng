#include <doctest/doctest.h>

#include <nrng/type_traits.hpp>

#include <execution>
#include <functional>

TEST_CASE("execution_policy") {
  CHECK(nrng::execution_policy<std::execution::sequenced_policy>);
  CHECK(not nrng::execution_policy<int>);
}

struct Unrelated {};
TEST_CASE("binary_closed_under") {
  CHECK(nrng::binary_closed_under<int, std::plus<>>);
  auto op = [](int /* unused */, int /* unused */) { return Unrelated{}; };
  CHECK(not nrng::binary_closed_under<int, decltype(op)>);
}

TEST_CASE("unary_closed_under") {
  CHECK(nrng::unary_closed_under<int, std::negate<>>);
  auto op = [](int /* unused */) { return Unrelated{}; };
  CHECK(not nrng::unary_closed_under<int, decltype(op)>);
}
