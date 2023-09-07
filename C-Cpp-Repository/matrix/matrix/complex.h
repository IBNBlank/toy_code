/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#ifndef MATRIX_COMPLEX_H_
#define MATRIX_COMPLEX_H_

#include <iostream>

namespace matrix {

class Complex {
 public:
  explicit Complex(double real = 0.0, double imag = 0.0)
      : real_(real), imag_(imag) {}

  inline double GetReal() const { return real_; }
  inline double GetImag() const { return imag_; }
  inline void SetReal(double real) { real_ = real; }
  inline void SetImag(double imag) { imag_ = imag; }

  inline double Norm() const { return real_ * real_ + imag_ * imag_; }
  inline Complex Conjugate() { return Complex(real_, -imag_); }

  Complex& operator+=(const Complex&);
  Complex& operator-=(const Complex&);
  Complex& operator*=(const Complex&);
  Complex& operator*=(double);
  Complex& operator/=(double);

 private:
  double real_;
  double imag_;

  friend inline Complex& __doapl(Complex*, const Complex&);
  friend inline Complex& __doami(Complex*, const Complex&);
  friend inline Complex& __doaml(Complex*, const Complex&);
};

// positive
const Complex& operator+(const Complex&);

// negative
Complex operator-(const Complex&);

// add
Complex operator+(const Complex&, const Complex&);
Complex operator+(const Complex&, double);
Complex operator+(double, const Complex&);

// subtract
Complex operator-(const Complex&, const Complex&);
Complex operator-(const Complex&, double);
Complex operator-(double, const Complex&);

// multiply
Complex operator*(const Complex&, const Complex&);
Complex operator*(const Complex&, double);
Complex operator*(double, const Complex&);

// divide
Complex operator/(const Complex&, double);

// equal
bool operator==(const Complex&, const Complex&);
bool operator==(const Complex&, double);
bool operator==(double, const Complex&);

// not equal
bool operator!=(const Complex&, const Complex&);
bool operator!=(const Complex&, double);
bool operator!=(double, const Complex&);

// output
std::ostream& operator<<(std::ostream&, const Complex&);

}  // namespace matrix

#endif  // MATRIX_COMPLEX_H_
