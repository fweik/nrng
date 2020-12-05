#include <doctest/doctest.h>

#include <nrng/reduce.hpp>

#include <numeric>
#include <array>

TEST_CASE("reduce iterator version without policy") {
  auto constexpr a = std::array{ 1, 2, 3, 4, 5 };
  /* plus version, default init */
  {
    auto constexpr expected = std::reduce(a.begin(), a.end());
    auto constexpr result = nrng::reduce(a.begin(), a.end());

    CHECK(expected == result);
  }

  /* plus version, with init */
  {
    auto constexpr init = 5;

    auto constexpr expected = std::reduce(a.begin(), a.end(), init);
    auto constexpr result = nrng::reduce(a.begin(), a.end(), init);

    CHECK(expected == result);
  }

  /* generic version */
  {
    auto constexpr init = 5;
    auto constexpr op = std::multiplies<>{};

    auto constexpr expected = std::reduce(a.begin(), a.end(), init, op);
    auto constexpr result = nrng::reduce(a.begin(), a.end(), init, op);

    CHECK(expected == result);
  }
}

TEST_CASE("reduce iterator version with policy") {
  auto constexpr a = std::array{ 1, 2, 3, 4, 5 };
  /* plus version, default init */
  {
    auto const expected = std::reduce(std::execution::par_unseq, a.begin(), a.end());
    auto const result = nrng::reduce(std::execution::par_unseq, a.begin(), a.end());

    CHECK(expected == result);
  }

  /* plus version, with init */
  {
    auto constexpr init = 5;

    auto const expected = std::reduce(std::execution::par_unseq, a.begin(), a.end(), init);
    auto const result = nrng::reduce(std::execution::par_unseq, a.begin(), a.end(), init);

    CHECK(expected == result);
  }

  /* generic version */
  {
    auto constexpr init = 5;
    auto constexpr op = std::multiplies<>{};

    auto const expected = std::reduce(std::execution::par_unseq, a.begin(), a.end(), init, op);
    auto const result = nrng::reduce(std::execution::par_unseq, a.begin(), a.end(), init, op);

    CHECK(expected == result);
  }
}
