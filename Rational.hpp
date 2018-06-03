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

  ~Rational() = default;

  constexpr Rational(const Rational& other) = default;
  constexpr Rational(Rational&& other) = default;

  constexpr Rational& operator =(const Rational& other) & = default;
  constexpr Rational& operator =(Rational&& other) & = default;

  constexpr Rational&& operator =(const Rational& other) && = delete;
  constexpr Rational&& operator =(Rational&& other) && = delete;


public:
  //------------------------------------------
  //
  //  Arithmetic unary operator
  //
  //------------------------------------------
  constexpr Rational operator +() const {
    return Rational{*this};
  }

  constexpr Rational operator -() const {
    Rational ret{*this};
    ret.numerator_ = -ret.numerator_;
    return ret;
  }

  constexpr Rational inverse() const {
    Rational ret{*this};
    if (numerator_ == static_cast<T>(0))
      throw ZeroDivisorException();
    T tmp = ret.numerator_;
    ret.numerator_ = ret.denominator_;
    ret.denominator_ = tmp;
    ret.normalize();
    return ret;
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


public:
  //------------------------------------------
  //
  //  Element access
  //
  //------------------------------------------
  constexpr const T& numerator() const {
    return numerator_;
  }

  constexpr const T& denominator() const {
    return denominator_;
  }

  // 整数ならtrue
  constexpr bool isInteger() const {
    return denominator_ == static_cast<T>(1);
  }

  // 零ならtrue
  constexpr bool isZero() const {
    return numerator_ == static_cast<T>(0);
  }


private:
  T numerator_ = static_cast<T>(0);
  T denominator_ = static_cast<T>(1);
};  //class Rational

}  //namespace rational
}  //namespace mylib

#endif
