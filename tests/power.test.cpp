#include <doctest/doctest.h>

#include <nrng/power.hpp>

TEST_CASE("power test") {
  CHECK(nrng::power<0>(247) == 1);
  CHECK(nrng::power<1>(247) == 247);
  CHECK(nrng::power<2>(247) == (247 * 247));
  CHECK(nrng::power<3>(3) == (3 * 3 * 3));
}