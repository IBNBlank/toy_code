/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#include "matrix/complex.h"

namespace matrix {

// private method
inline Complex& __doapl(Complex* left, const Complex& right) {
  left->real_ += right.real_;
  left->imag_ += right.imag_;
  return *left;
}

inline Complex& __doami(Complex* left, const Complex& right) {
  left->real_ -= right.real_;
  left->imag_ -= right.imag_;
  return *left;
}

inline Complex& __doaml(Complex* left, const Complex& right) {
  double temp_real = left->real_ * right.real_ - left->imag_ * right.imag_;
  left->imag_ = left->real_ * right.imag_ + left->imag_ * right.real_;
  left->real_ = temp_real;
  return *left;
}

// class operator overloading
Complex& Complex::operator+=(const Complex& right) {
  return __doapl(this, right);
}

Complex& Complex::operator-=(const Complex& right) {
  return __doami(this, right);
}

Complex& Complex::operator*=(const Complex& right) {
  return __doaml(this, right);
}

Complex& Complex::operator*=(double right) {
  this->real_ *= right;
  this->imag_ *= right;
  return *this;
}

Complex& Complex::operator/=(double right) {
  this->real_ /= right;
  this->imag_ /= right;
  return *this;
}

// global operator overloading
// positive
const Complex& operator+(const Complex& complex) { return complex; }

// negative
Complex operator-(const Complex& complex) {
  return Complex(-complex.GetReal(), -complex.GetImag());
}

// add
Complex operator+(const Complex& x, const Complex& y) {
  return Complex(x.GetReal() + y.GetReal(), x.GetImag() + y.GetImag());
}

Complex operator+(const Complex& x, double y) {
  return Complex(x.GetReal() + y, x.GetImag());
}

Complex operator+(double x, const Complex& y) {
  return Complex(x + y.GetReal(), y.GetImag());
}

// subtract
Complex operator-(const Complex& x, const Complex& y) {
  return Complex(x.GetReal() - y.GetReal(), x.GetImag() - y.GetImag());
}

Complex operator-(const Complex& x, double y) {
  return Complex(x.GetReal() - y, x.GetImag());
}

Complex operator-(double x, const Complex& y) {
  return Complex(x - y.GetReal(), -y.GetImag());
}

// multiply
Complex operator*(const Complex& x, const Complex& y) {
  return Complex(x.GetReal() * y.GetReal() - x.GetImag() * y.GetImag(),
                 x.GetReal() * y.GetImag() + x.GetImag() * y.GetReal());
}

Complex operator*(const Complex& x, double y) {
  return Complex(x.GetReal() * y, x.GetImag() * y);
}

Complex operator*(double x, const Complex& y) {
  return Complex(x * y.GetReal(), x * y.GetImag());
}

// divide
Complex operator/(const Complex& x, double y) {
  return Complex(x.GetReal() / y, x.GetImag() / y);
}

// equal
bool operator==(const Complex& x, const Complex& y) {
  return (x.GetReal() == y.GetReal()) && (x.GetImag() == y.GetImag());
}

bool operator==(const Complex& x, double y) {
  return (x.GetReal() == y) && (x.GetImag() == 0.0);
}

bool operator==(double x, const Complex& y) {
  return (x == y.GetReal()) && (0.0 == y.GetImag());
}

// not equal
bool operator!=(const Complex& x, const Complex& y) {
  return (x.GetReal() != y.GetReal()) || (x.GetImag() != y.GetImag());
}

bool operator!=(const Complex& x, double y) {
  return (x.GetReal() != y) || (x.GetImag() != 0.0);
}

bool operator!=(double x, const Complex& y) {
  return (x != y.GetReal()) || (0.0 != y.GetImag());
}

// output
std::ostream& operator<<(std::ostream& os, const Complex& complex) {
  return os << complex.GetReal() << '+' << complex.GetImag() << 'i';
}

}  // namespace matrix
