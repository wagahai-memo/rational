#include <iostream>
#include "Rational.hpp"

template <typename T>
using R = mylib::rational::Rational<T>;

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

  return 0;
}
