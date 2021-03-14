#include <doctest/doctest.h>

#include <nrng/moment.hpp>

TEST_CASE("moments exists") {
  auto const values = std::array{1., 2., 3., 4., 5.};
  auto const result = nrng::moment<2>(values);

  auto const expected =
      nrng::accumulate(values, 0., [](auto s, auto v) { return s + v * v; }) /
      values.size();

  CHECK(result == expected);
}

TEST_CASE("mean") {
  auto const values = std::array{1., 2., 3., 4., 5.};
  auto const expected = nrng::moment<1>(values);

  CHECK(nrng::mean(values) == expected);
  CHECK(nrng::mean(values.begin(), values.end()) == expected);
}