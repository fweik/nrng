#include <doctest/doctest.h>

#include <nrng/partial_sum.hpp>

#include <array>
#include <functional>
#include <numeric>
#include <iterator>

TEST_CASE("iterator version, with op") {
  auto constexpr a = std::array{2., 4., 5., 6., 7.};
  auto expected = std::array{a};
  std::partial_sum(a.begin(), a.end(), expected.begin(), std::multiplies<>{});

  {
    auto result = std::array{a};
    auto const ret = nrng::partial_sum(
        std::counted_iterator{a.begin(), a.size()}, std::default_sentinel,
        result.begin(), std::multiplies<>{});

    CHECK(ret == result.end());
    CHECK(result == expected);
  }

  {
    auto result = std::array{a};
    auto const ret = nrng::partial_sum(a, result.begin(), std::multiplies<>{});

    CHECK(ret == result.end());
    CHECK(result == expected);
  }

  {
    auto result = std::array{a};
    auto const ret = nrng::partial_sum(a, result, std::multiplies<>{});

    CHECK(ret == result.end());
    CHECK(result == expected);
  }  
}

TEST_CASE("with default op") {
  auto constexpr a = std::array{2., 4., 5., 6., 7.};
  auto expected = std::array{a};
  std::partial_sum(a.begin(), a.end(), expected.begin());

  {
    auto result = std::array{a};
    auto const ret =
        nrng::partial_sum(std::counted_iterator{a.begin(), a.size()},
                          std::default_sentinel, result.begin());

    CHECK(ret == result.end());
    CHECK(result == expected);
  }

  {
    auto result = std::array{a};
    auto const ret = nrng::partial_sum(a, result.begin());

    CHECK(ret == result.end());
    CHECK(result == expected);
  }
}
