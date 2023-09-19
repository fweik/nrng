#include <doctest/doctest.h>

#include <nrng/central_moment.hpp>

using nrng::moment;
using nrng::central_moment;
using nrng::mean;
using nrng::variance;
using nrng::standard_deviation;

TEST_CASE("first central moment") {
  auto const values = std::array{1., 2., 3., 4., 5.};

  CHECK(central_moment<1>(values) == 0);
  CHECK(central_moment<1>(values.begin(), values.end()) == central_moment<1>(values));
}

TEST_CASE("second central moment") {
  auto const values = std::array{1., 2., 3., 4., 5.};
  auto shift_by_mean = [mu = mean(values)](auto v) { return v - mu; };

  CHECK(central_moment<2>(values) == moment<2>(values | std::views::transform(shift_by_mean)));
}

TEST_CASE("variance") {
  auto const values = std::array{1., 2., 3., 4., 5.};

  CHECK(variance(values) == central_moment<2>(values));
}

TEST_CASE("standard deviation") {
  auto const values = std::array{1., 2., 3., 4., 5.};

  CHECK(standard_deviation(values) == std::sqrt(variance(values)));
}