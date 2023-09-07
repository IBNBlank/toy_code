/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#ifndef MATRIX_MATRIX2D_H_
#define MATRIX_MATRIX2D_H_

#include <iostream>

#include "matrix/vector.h"

namespace matrix {

class Matrix2D {
 public:
  // constructor
  explicit Matrix2D(uint32_t row = 1, uint32_t column = 1,
                    const Complex* value_list = 0);

  // big three
  Matrix2D(const Matrix2D&);
  inline ~Matrix2D() { delete[] pointer_; }
  Matrix2D& operator=(const Matrix2D&);

  // get element
  inline double GetRow() const { return row_; }
  inline double GetColumn() const { return column_; }
  inline Vector* GetPointer() const { return pointer_; }
  Vector& operator[](uint32_t);

  // assignment
  Matrix2D& operator+=(const Matrix2D&);
  Matrix2D& operator-=(const Matrix2D&);
  Matrix2D& operator*=(double);
  Matrix2D& operator/=(double);

 private:
  uint32_t row_;
  uint32_t column_;
  Vector* pointer_;

  friend inline Matrix2D& __doapl(Matrix2D*, const Matrix2D&);
  friend inline Matrix2D& __doami(Matrix2D*, const Matrix2D&);
};

// add
Matrix2D operator+(const Matrix2D&, const Matrix2D&);

// subtract
Matrix2D operator-(const Matrix2D&, const Matrix2D&);

// multiply
Matrix2D operator*(const Matrix2D&, const Matrix2D&);
Matrix2D operator*(const Matrix2D&, double);
Matrix2D operator*(double, const Matrix2D&);

// divide
Matrix2D operator/(const Matrix2D&, double);

// equal
bool operator==(const Matrix2D&, const Matrix2D&);

// not equal
bool operator!=(const Matrix2D&, const Matrix2D&);

// output
std::ostream& operator<<(std::ostream&, const Matrix2D&);

}  // namespace matrix

#endif  // MATRIX_MATRIX2D_H_
