#include <doctest/doctest.h>

#include <nrng/accumulate.hpp>

#include <array>
#include <functional>
#include <numeric>

TEST_CASE("accumulate iterator version") {
  auto constexpr a = std::array{1, 2, 3, 4, 5};
  /* plus version */
  {
    auto constexpr expected = std::accumulate(a.begin(), a.end(), 0);
    auto constexpr result = nrng::accumulate(a.begin(), a.end(), 0);

    CHECK(expected == result);
  }

  /* op version */
  {
    auto constexpr expected =
        std::accumulate(a.begin(), a.end(), 1, std::multiplies<>{});
    auto constexpr result =
        nrng::accumulate(a.begin(), a.end(), 1, std::multiplies<>{});

    CHECK(expected == result);
  }
}

TEST_CASE("accumulate range version") {
  auto constexpr a = std::array{1, 2, 3, 4, 5};
  /* plus version */
  {
    auto constexpr expected = std::accumulate(a.begin(), a.end(), 0);
    auto constexpr result = nrng::accumulate(a, 0);

    CHECK(expected == result);
  }

  /* op version */
  {
    auto constexpr expected =
        std::accumulate(a.begin(), a.end(), 1, std::multiplies<>{});
    auto constexpr result = nrng::accumulate(a, 1, std::multiplies<>{});

    CHECK(expected == result);
  }
}