#include <doctest/doctest.h>

#include <nrng/adjacent_difference.hpp>

#include <iostream>
#include <sstream>
#include <array>

TEST_CASE("adjacent_difference iterator version, with input iterator")
{
  /* Normal case */
  {
    using namespace std::string_literals;
    auto const numbers = "1 2 3 4 5"s;

    std::istringstream str1(numbers);
    std::vector<int> result;
    nrng::adjacent_difference(std::istream_iterator<int>(str1), std::istream_iterator<int>(), std::back_inserter(result));

    std::istringstream str2(numbers);
    std::vector<int> expected;
    std::adjacent_difference(std::istream_iterator<int>(str2), std::istream_iterator<int>(), std::back_inserter(expected));

    CHECK(result == expected);
  }

  /* Edge case empty range */
  {
    int dummy{};
    auto const ret = nrng::adjacent_difference(std::istream_iterator<int>(), std::istream_iterator<int>(), &dummy);
    CHECK(ret.in == std::istream_iterator<int>());
    CHECK(ret.out == &dummy);
  }
}

TEST_CASE("adjacent_difference iterator version, with forward iterator")
{
  /* Normal case */
  {
    auto const a = std::array{ 1, 2, 3, 4, 5 };
    std::vector<int> result;
    auto ret = nrng::adjacent_difference(std::counted_iterator{ a.begin(), a.size() }, std::default_sentinel, std::back_inserter(result));
    CHECK(ret.in == (std::counted_iterator{ a.begin(), a.size() } + a.size()));

    std::vector<int> expected;
    std::adjacent_difference(a.begin(), a.end(), std::back_inserter(expected));

    CHECK(result == expected);
  }

  /* Edge case empty range */
  {
    auto empty = std::array<int, 0>{};
    auto const ret = nrng::adjacent_difference(empty.begin(), empty.end(), empty.begin());
    CHECK(ret.in == empty.begin());
    CHECK(ret.out == empty.begin());
  }
}

TEST_CASE("adjacent_difference iterator version, with op")
{
  auto const a = std::array{ 1, 2, 3, 4, 5 };
  std::vector<int> result;
  auto ret = nrng::adjacent_difference(std::counted_iterator{ a.begin(), a.size() }, std::default_sentinel, std::back_inserter(result), std::multiplies<>{});
  CHECK(ret.in == (std::counted_iterator{ a.begin(), a.size() } + a.size()));

  std::vector<int> expected;
  std::adjacent_difference(a.begin(), a.end(), std::back_inserter(expected), std::multiplies<>{});

  CHECK(result == expected);
}

TEST_CASE("adjacent_difference range version")
{
  auto const a = std::array{ 1, 2, 3, 4, 5 };
  std::vector<int> result;
  auto const ret = nrng::adjacent_difference(a, std::back_inserter(result));
  CHECK(ret.in == a.end());

  std::vector<int> expected;
  std::adjacent_difference(a.begin(), a.end(), std::back_inserter(expected));

  CHECK(result == expected);
}

TEST_CASE("adjacent_difference range version, with execution policy")
{
  auto const a = std::array{ 1, 2, 3, 4, 5 };
  std::array<int, a.size()> result{};
  auto const ret = nrng::adjacent_difference(std::execution::par, a, result.begin());
  CHECK(ret.in == a.end());

  std::array<int, a.size()> expected{};
  std::adjacent_difference(std::execution::par, a.begin(), a.end(), expected.begin());

  CHECK(result == expected);
}

TEST_CASE("adjacent_difference range version, with op")
{
  auto const a = std::array{ 1, 2, 3, 4, 5 };
  std::vector<int> result;
  auto const ret = nrng::adjacent_difference(a, std::back_inserter(result), std::multiplies<>{});
  CHECK(ret.in == a.end());

  std::vector<int> expected;
  std::adjacent_difference(a.begin(), a.end(), std::back_inserter(expected), std::multiplies<>{});

  CHECK(result == expected);
}

TEST_CASE("adjacent_difference range version with execution policy, with op")
{
  auto const a = std::array{ 1, 2, 3, 4, 5 };
  std::array<int, a.size()> result{};
  auto const ret = nrng::adjacent_difference(std::execution::par, a, result.begin(), std::multiplies<>{});
  CHECK(ret.in == a.end());

  std::array<int, a.size()> expected{};
  std::adjacent_difference(std::execution::par, a.begin(), a.end(), expected.begin(), std::multiplies<>{});

  CHECK(result == expected);
}
