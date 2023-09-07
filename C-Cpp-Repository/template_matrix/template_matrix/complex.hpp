/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#ifndef TEMPLATE_MATRIX_COMPLEX_HPP_
#define TEMPLATE_MATRIX_COMPLEX_HPP_

#include <iostream>

namespace template_matrix {

template <class T>
class Complex {
 public:
  explicit Complex(T real = 0.0, T imag = 0.0) : real_(real), imag_(imag) {}

  inline T GetReal() const { return real_; }
  inline T GetImag() const { return imag_; }
  inline void SetReal(T real) { real_ = real; }
  inline void SetImag(T imag) { imag_ = imag; }

  inline T Norm() const { return real_ * real_ + imag_ * imag_; }
  inline Complex Conjugate() { return Complex(real_, -imag_); }

  Complex& operator+=(const Complex&);
  Complex& operator-=(const Complex&);
  Complex& operator*=(const Complex&);
  Complex& operator*=(T);
  Complex& operator/=(T);

 private:
  T real_;
  T imag_;

  friend inline Complex& __doapl(Complex* left, const Complex& right) {
    left->real_ += right.real_;
    left->imag_ += right.imag_;
    return *left;
  }

  friend inline Complex& __doami(Complex* left, const Complex& right) {
    left->real_ -= right.real_;
    left->imag_ -= right.imag_;
    return *left;
  }

  friend inline Complex& __doaml(Complex* left, const Complex& right) {
    T temp_real = left->real_ * right.real_ - left->imag_ * right.imag_;
    left->imag_ = left->real_ * right.imag_ + left->imag_ * right.real_;
    left->real_ = temp_real;
    return *left;
  }
};

// class operator overloading
template <class T>
Complex<T>& Complex<T>::operator+=(const Complex<T>& right) {
  return __doapl(this, right);
}

template <class T>
Complex<T>& Complex<T>::operator-=(const Complex<T>& right) {
  return __doami(this, right);
}

template <class T>
Complex<T>& Complex<T>::operator*=(const Complex<T>& right) {
  return __doaml(this, right);
}

template <class T>
Complex<T>& Complex<T>::operator*=(T right) {
  this->real_ *= right;
  this->imag_ *= right;
  return *this;
}

template <class T>
Complex<T>& Complex<T>::operator/=(T right) {
  this->real_ /= right;
  this->imag_ /= right;
  return *this;
}

// global operator overloading
// positive
template <class T>
const Complex<T>& operator+(const Complex<T>& complex) {
  return complex;
}

// negative
template <class T>
Complex<T> operator-(const Complex<T>& complex) {
  return Complex<T>(-complex.GetReal(), -complex.GetImag());
}

// add
template <class T>
Complex<T> operator+(const Complex<T>& x, const Complex<T>& y) {
  return Complex<T>(x.GetReal() + y.GetReal(), x.GetImag() + y.GetImag());
}

template <class T>
Complex<T> operator+(const Complex<T>& x, T y) {
  return Complex<T>(x.GetReal() + y, x.GetImag());
}

template <class T>
Complex<T> operator+(T x, const Complex<T>& y) {
  return Complex<T>(x + y.GetReal(), y.GetImag());
}

// subtract
template <class T>
Complex<T> operator-(const Complex<T>& x, const Complex<T>& y) {
  return Complex<T>(x.GetReal() - y.GetReal(), x.GetImag() - y.GetImag());
}

template <class T>
Complex<T> operator-(const Complex<T>& x, T y) {
  return Complex<T>(x.GetReal() - y, x.GetImag());
}

template <class T>
Complex<T> operator-(T x, const Complex<T>& y) {
  return Complex<T>(x - y.GetReal(), -y.GetImag());
}

// multiply
template <class T>
Complex<T> operator*(const Complex<T>& x, const Complex<T>& y) {
  return Complex<T>(x.GetReal() * y.GetReal() - x.GetImag() * y.GetImag(),
                    x.GetReal() * y.GetImag() + x.GetImag() * y.GetReal());
}

template <class T>
Complex<T> operator*(const Complex<T>& x, T y) {
  return Complex<T>(x.GetReal() * y, x.GetImag() * y);
}

template <class T>
Complex<T> operator*(T x, const Complex<T>& y) {
  return Complex<T>(x * y.GetReal(), x * y.GetImag());
}

// divide
template <class T>
Complex<T> operator/(const Complex<T>& x, T y) {
  return Complex<T>(x.GetReal() / y, x.GetImag() / y);
}

// equal
template <class T>
bool operator==(const Complex<T>& x, const Complex<T>& y) {
  return (x.GetReal() == y.GetReal()) && (x.GetImag() == y.GetImag());
}

template <class T>
bool operator==(const Complex<T>& x, T y) {
  return (x.GetReal() == y) && (x.GetImag() == 0.0);
}

template <class T>
bool operator==(T x, const Complex<T>& y) {
  return (x == y.GetReal()) && (0.0 == y.GetImag());
}

// not equal
template <class T>
bool operator!=(const Complex<T>& x, const Complex<T>& y) {
  return (x.GetReal() != y.GetReal()) || (x.GetImag() != y.GetImag());
}

template <class T>
bool operator!=(const Complex<T>& x, T y) {
  return (x.GetReal() != y) || (x.GetImag() != 0.0);
}

template <class T>
bool operator!=(T x, const Complex<T>& y) {
  return (x != y.GetReal()) || (0.0 != y.GetImag());
}

// output
template <class T>
std::ostream& operator<<(std::ostream& os, const Complex<T>& complex) {
  return os << complex.GetReal() << '+' << complex.GetImag() << 'i';
}

}  // namespace template_matrix

#endif  // TEMPLATE_MATRIX_COMPLEX_HPP_
