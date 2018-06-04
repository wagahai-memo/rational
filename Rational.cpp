#include <iostream>
#include "Rational.hpp"

template <typename T>
using R = mylib::rational::Rational<T>;


constexpr R<int> plus_eq(const R<int> x)
{
  R<int> ret(1, 2);
  return ret += x;
}

constexpr R<int> minus_eq(const R<int> x)
{
  R<int> ret(1, 2);
  return ret -= x;
}

constexpr R<int> multiply_eq(const R<int> x)
{
  R<int> ret(1, 2);
  return ret *= x;
}



int main()
{
  R<int> x, y(3), z(3, -2);
  std::cout << x << std::endl;
  std::cout << y << std::endl;
  std::cout << z << std::endl;

  R<int> a;
  try {
    std::cin >> a;
    std::cout << a << std::endl;
  } catch (ZeroDivisorException& e) {
    std::cout << e.what() << std::endl;
  }

  static_assert(R<int>(2, -4) == R<int>(-1, 2), "");
  static_assert(R<int>(1, 3) < R<int>(1, 2), "");
  static_assert(R<int>(-21, 3).isInteger(), "");
  static_assert(R<int>().isZero(), "");
  static_assert(R<int>(2, 3).numerator(), "");
  static_assert(R<int>(2, 3).denominator(), "");
  static_assert(+R<int>(2, 3) == R<int>(2, 3), "");
  static_assert(-R<int>(2, 3) == R<int>(-2, 3), "");
  std::cout << R<int>(5, 13).inverse() << std::endl;
  static_assert(plus_eq(R<int>(3, 5)) == R<int>(11, 10), "");
  static_assert(minus_eq(R<int>(3, 5)) == R<int>(-1, 10), "");
  static_assert(multiply_eq(R<int>(3, 5)) == R<int>(3, 10), "");
  R<int> b(2);
  std::cout << (b /= b.inverse()) << std::endl;
  static_assert(R<int>(1, 2) + R<int>(1, 3) == R<int>(5, 6), "");
  static_assert(R<int>(1, 2) - R<int>(1, 3) == R<int>(1, 6), "");
  static_assert(R<int>(1, 2) * R<int>(1, 3) == R<int>(1, 6), "");
  std::cout << (b / b) << std::endl;

  return 0;
}
