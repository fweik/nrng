#include <doctest/doctest.h>

#include <nrng/transform_reduce.hpp>

#include <array>
#include <numeric>

/*
template<class InputIt1, class InputIt2, class T>
constexpr T transform_reduce(InputIt1 first1, InputIt1 last1, InputIt2 first2, T
init);
*/
TEST_CASE("transform_reduce, unary version, iterator version") {
  auto constexpr a = std::array{1, 2, 3};
  auto constexpr b = std::array{2., 4., 5., 6., 7.};
  auto constexpr expected =
      std::transform_reduce(a.begin(), a.end(), b.begin(), 0.);

  {
    auto constexpr result = nrng::transform_reduce(
        std::counted_iterator{a.begin(), a.size()}, std::default_sentinel,
        std::counted_iterator{b.begin(), b.size()}, std::default_sentinel, 0.);

    CHECK(result == expected);
  }

  {
    auto const result = nrng::transform_reduce(
        std::execution::par_unseq, std::counted_iterator{a.begin(), a.size()},
        std::default_sentinel, std::counted_iterator{b.begin(), b.size()},
        std::default_sentinel, 0.);

    CHECK(result == expected);
  }
}

TEST_CASE("transform_reduce, unary version, range version") {
  auto constexpr a = std::array{1, 2, 3};
  auto constexpr b = std::array{2., 4., 5., 6., 7.};

  auto constexpr result = nrng::transform_reduce(a, b, 0.);

  auto constexpr expected =
      std::transform_reduce(a.begin(), a.end(), b.begin(), 0.);

  CHECK(result == expected);
}

/*
template <class InputIt1, class InputIt2, class T, class BinaryOp1, class
BinaryOp2> constexpr T transform_reduce(InputIt1 first1, InputIt1 last1,
InputIt2 first2, T init, BinaryOp1 binary_op1, BinaryOp2 binary_op2);
*/
TEST_CASE("transform_reduce, binary version, iterator version, with ops") {
  auto constexpr a = std::array{1, 2, 3};
  auto constexpr b = std::array{2., 4., 5., 6., 7.};

  auto constexpr expected = std::transform_reduce(
      a.begin(), a.end(), b.begin(), 0., std::divides<>{}, std::multiplies<>{});

  {
    auto constexpr result = nrng::transform_reduce(
        std::counted_iterator{a.begin(), a.size()}, std::default_sentinel,
        std::counted_iterator{b.begin(), b.size()}, std::default_sentinel, 0.,
        std::divides<>{}, std::multiplies<>{});

    CHECK(result == expected);
  }

  {
    auto const result = nrng::transform_reduce(
        std::execution::par_unseq, std::counted_iterator{a.begin(), a.size()},
        std::default_sentinel, std::counted_iterator{b.begin(), b.size()},
        std::default_sentinel, 0., std::divides<>{}, std::multiplies<>{});

    CHECK(result == expected);
  }
}

TEST_CASE("transform_reduce, binary version, range version, with ops") {
  auto constexpr a = std::array{1, 2, 3};
  auto constexpr b = std::array{2., 4., 5., 6., 7.};

  auto constexpr result =
      nrng::transform_reduce(a, b, 0., std::divides<>{}, std::multiplies<>{});

  auto constexpr expected = std::transform_reduce(
      a.begin(), a.end(), b.begin(), 0., std::divides<>{}, std::multiplies<>{});

  CHECK(result == expected);
}

/*
template<class InputIt, class T, class BinaryOp, class UnaryOp>
constexpr T transform_reduce(InputIt first, InputIt last,
                             T init, BinaryOp binop, UnaryOp unary_op);
*/
TEST_CASE("transform_reduce, unary version, iterator version") {
  auto constexpr a = std::array{1, 2, 3, 4, 5};
  auto constexpr unary_op = [](auto e) { return e * e; };
  auto constexpr expected =
      std::transform_reduce(a.begin(), a.end(), 1, std::plus<>{}, unary_op);

  {
    auto constexpr result = nrng::transform_reduce(
        std::counted_iterator{a.begin(), a.size()}, std::default_sentinel, 1,
        std::plus<>{}, unary_op);
    CHECK(result == expected);
  }

  {
    auto const result = nrng::transform_reduce(
        std::execution::par_unseq, std::counted_iterator{a.begin(), a.size()},
        std::default_sentinel, 1, std::plus<>{}, unary_op);
    CHECK(result == expected);
  }
}

TEST_CASE("transform_reduce, unary version, range version") {
  auto constexpr a = std::array{1, 2, 3, 4, 5};
  auto constexpr unary_op = [](auto e) { return e * e; };

  auto constexpr result = nrng::transform_reduce(a, 1, std::plus<>{}, unary_op);
  auto constexpr expected =
      std::transform_reduce(a.begin(), a.end(), 1, std::plus<>{}, unary_op);

  CHECK(result == expected);
}
