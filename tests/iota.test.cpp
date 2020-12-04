#include <doctest/doctest.h>

#include <nrng/iota.hpp>

#include <array>

TEST_CASE("iota iterator version")
{
  auto const init = 4.F;
  auto constexpr elements = 5;

  std::array<float, elements> expected{};
  std::iota(expected.begin(), expected.end(), init);

  std::array<float, elements> result{};
  auto const *out = nrng::iota(result.begin(), result.end(), init);

  CHECK(out == result.begin() + elements);
  CHECK(expected == result);
}

TEST_CASE("iota range version")
{
  auto const init = 4.F;
  auto constexpr elements = 5;

  std::array<float, elements> expected{};
  std::iota(expected.begin(), expected.end(), init);

  /* with l-value range */
  {
    std::array<float, elements> result{};
    auto const *out = nrng::iota(result, init);

    CHECK(out == result.begin() + elements);
    CHECK(expected == result);
  }

  /* with r-value range */
  {
    static_assert(std::is_same_v<
      decltype(
        nrng::iota(std::array<float, elements>{}, init)),
      std::ranges::dangling>);
  }
}