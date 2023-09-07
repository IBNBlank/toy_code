/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#ifndef MATRIX_MATRIX3D_H_
#define MATRIX_MATRIX3D_H_

#include <iostream>

#include "matrix/matrix2d.h"

namespace matrix {

class Matrix3D {
 public:
  // constructor
  explicit Matrix3D(uint32_t row = 1, uint32_t column = 1, uint32_t length = 1,
                    const Complex* value_list = 0);

  // big three
  Matrix3D(const Matrix3D&);
  inline ~Matrix3D() { delete[] pointer_; }
  Matrix3D& operator=(const Matrix3D&);

  // get element
  inline double GetRow() const { return row_; }
  inline double GetColumn() const { return column_; }
  inline double GetLength() const { return length_; }
  inline Matrix2D* GetPointer() const { return pointer_; }
  Matrix2D& operator[](uint32_t);

  // assignment
  Matrix3D& operator+=(const Matrix3D&);
  Matrix3D& operator-=(const Matrix3D&);
  Matrix3D& operator*=(double);
  Matrix3D& operator/=(double);

 private:
  uint32_t row_;
  uint32_t column_;
  uint32_t length_;
  Matrix2D* pointer_;

  friend inline Matrix3D& __doapl(Matrix3D*, const Matrix3D&);
  friend inline Matrix3D& __doami(Matrix3D*, const Matrix3D&);
};

// add
Matrix3D operator+(const Matrix3D&, const Matrix3D&);

// subtract
Matrix3D operator-(const Matrix3D&, const Matrix3D&);

// multiply
Matrix3D operator*(const Matrix3D&, double);
Matrix3D operator*(double, const Matrix3D&);

// divide
Matrix3D operator/(const Matrix3D&, double);

// equal
bool operator==(const Matrix3D&, const Matrix3D&);

// not equal
bool operator!=(const Matrix3D&, const Matrix3D&);

// output
std::ostream& operator<<(std::ostream&, const Matrix3D&);

}  // namespace matrix

#endif  // MATRIX_MATRIX3D_H_
