#ifndef MYLIB_RATIONAL_HPP_
#define MYLIB_RATIONAL_HPP_
#include <ostream>
#include "../ZeroDivisorException.hpp"
#include "../integer/gcd.hpp"


namespace mylib {
namespace rational {

template <typename T>
class Rational {
  friend std::ostream& operator <<(std::ostream& os, const Rational& x) {
    return os << x.numerator_ << "/" << x.denominator_;
  }

  friend std::istream& operator >>(std::istream& is, Rational& x) {
    T n, d;
    std::istream::char_type c;

    is >> n >> c;
    if (c == '/') {
      is >> d;
      x = Rational(n, d);
    } else {
      is.putback(c);
      x = Rational(n);
    }

    return is;
  }


private:
  //------------------------------------------
  //
  //  既約分数にする
  //
  //------------------------------------------
  constexpr void normalize() {
    T g = mylib::gcd(numerator_, denominator_);
    numerator_ /= g;
    denominator_ /= g;
    if (denominator_ < 0) {
      numerator_ *= -1;
      denominator_ *= -1;
    }
  }


public:
  //------------------------------------------
  //
  //  Constructor, Destructor, Copy, Move
  //
  //------------------------------------------
  constexpr Rational() noexcept {}

  constexpr Rational(const T& n) noexcept : numerator_(n) {}

  constexpr Rational(const T& n, const T& d) : numerator_(n), denominator_(d) {
    if (d == 0)
      throw ZeroDivisorException();
    normalize();
  }


  //------------------------------------------
  //
  //  Logical operator
  //
  //------------------------------------------
private:
  constexpr T cmp(const Rational& other) const {
    return numerator_ * other.denominator_ - other.numerator_ * denominator_;
  }

public:
  constexpr bool operator ==(const Rational& other) const {
    return cmp(other) == 0;
  }

  constexpr bool operator !=(const Rational& other) const {
    return !(*this == other);
  }

  constexpr bool operator <(const Rational& other) const {
    return cmp(other) < 0;
  }

  constexpr bool operator >(const Rational& other) const {
    return cmp(other) > 0;
  }

  constexpr bool operator <=(const Rational& other) const {
    return !(*this > other);
  }

  constexpr bool operator >=(const Rational& other) const {
    return !(*this < other);
  }


private:
  T numerator_ = static_cast<T>(0);
  T denominator_ = static_cast<T>(1);
};  //class Rational

}  //namespace rational
}  //namespace mylib

#endif
