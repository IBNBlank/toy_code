/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#ifndef MATRIX_VECTOR_H_
#define MATRIX_VECTOR_H_

#include <iostream>

#include "matrix/complex.h"

namespace matrix {

class Vector {
 public:
  // constructor
  explicit Vector(uint32_t length = 1, const Complex* value_list = 0);

  // big three
  Vector(const Vector&);
  inline ~Vector() { delete[] pointer_; }
  Vector& operator=(const Vector&);

  // get element
  inline double GetLength() const { return length_; }
  inline Complex* GetPointer() const { return pointer_; }
  Complex& operator[](uint32_t);

  // assignment
  Vector& operator+=(const Vector&);
  Vector& operator-=(const Vector&);
  Vector& operator*=(double);
  Vector& operator/=(double);

 private:
  uint32_t length_;
  Complex* pointer_;

  friend inline Vector& __doapl(Vector*, const Vector&);
  friend inline Vector& __doami(Vector*, const Vector&);
};

// add
Vector operator+(const Vector&, const Vector&);

// subtract
Vector operator-(const Vector&, const Vector&);

// multiply
Vector operator*(const Vector&, const Vector&);
Vector operator*(const Vector&, double);
Vector operator*(double, const Vector&);

// divide
Vector operator/(const Vector&, double);

// equal
bool operator==(const Vector&, const Vector&);

// not equal
bool operator!=(const Vector&, const Vector&);

// output
std::ostream& operator<<(std::ostream&, const Vector&);

}  // namespace matrix

#endif  // MATRIX_VECTOR_H_
