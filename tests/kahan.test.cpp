#include <doctest/doctest.h>

#include <nrng/kahan.hpp>

#include <array>

TEST_CASE("kahan_plus result test") {
  /* Test numbers, chosen such that there are not
   * enought significant places in float for direct
   * summation to yield the correct result. */
  auto const init = 1000000.0F;
  auto const t1 = 3.14159F;
  auto const t2 = 2.71828F;
  auto const expected = 1000005.85987F;
  /* Make sure the direct summation does not yield the
   * correct result. */
  CHECK((init + t1 + t2) != expected);

  auto const summer = nrng::kahan_plus<float>{};
  auto const s1 = summer(init, t1);
  auto const s2 = summer(s1, t2);
  CHECK(s2.sum == expected);
}

TEST_CASE("kahan_sum_state is convertible to the scalar type") {
  static_assert(std::convertible_to<nrng::kahan_sum_state<int>, int>);
}

TEST_CASE("kahan sum, iterator version") {
  auto const vals = std::array{1., 2., 3.};
  auto const expected =
      nrng::kahan_plus<float>{}(nrng::kahan_plus<float>{}(1., 2.), 3.);

  CHECK_EQ(nrng::kahan_sum(vals.begin(), vals.end(), 0.), expected);
}

TEST_CASE("kahan sum, range version") {
  auto const vals = std::array{1., 2., 3.};

  CHECK_EQ(nrng::kahan_sum(vals, 0.),
           nrng::kahan_sum(vals.begin(), vals.end(), 0.));
}
