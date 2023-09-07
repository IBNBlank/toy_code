/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/
#include "matrix/matrix3d.h"

#include <string.h>

namespace matrix {
// constructor
Matrix3D::Matrix3D(uint32_t row, uint32_t column, uint32_t length,
                   const Complex* value_list)
    : row_(row), column_(column), length_(length) {
  if (row_ == 0 || column_ == 0 || length_ == 0) {
    row_ = 1;
    column_ = 1;
    length_ = 1;
  }
  pointer_ = new Matrix2D[row_];
  if (value_list) {
    for (uint32_t i = 0; i < row_; i++) {
      pointer_[i] =
          Matrix2D(column_, length_, value_list + i * column_ * length_);
    }
  } else {
    for (uint32_t i = 0; i < row_; i++) {
      pointer_[i] = Matrix2D(column_, length_);
    }
  }
}

// big three
Matrix3D::Matrix3D(const Matrix3D& matrix_3d) {
  row_ = matrix_3d.GetRow();
  column_ = matrix_3d.GetColumn();
  length_ = matrix_3d.GetLength();
  pointer_ = new Matrix2D[row_];
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] = matrix_3d.GetPointer()[i];
  }
}

Matrix3D& Matrix3D::operator=(const Matrix3D& matrix_3d) {
  if (this == &matrix_3d) {
    return *this;
  }

  delete[] pointer_;

  row_ = matrix_3d.GetRow();
  column_ = matrix_3d.GetColumn();
  length_ = matrix_3d.GetLength();
  pointer_ = new Matrix2D[row_];
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] = matrix_3d.GetPointer()[i];
  }

  return *this;
}

// private method
inline Matrix3D& __doapl(Matrix3D* left, const Matrix3D& right) {
  if (left->row_ == right.row_ && left->column_ == right.column_ &&
      left->length_ == right.length_) {
    for (uint32_t i = 0; i < left->row_; i++) {
      left->pointer_[i] += right.pointer_[i];
    }
  }

  return *left;
}

inline Matrix3D& __doami(Matrix3D* left, const Matrix3D& right) {
  if (left->row_ == right.row_ && left->column_ == right.column_ &&
      left->length_ == right.length_) {
    for (uint32_t i = 0; i < left->row_; i++) {
      left->pointer_[i] -= right.pointer_[i];
    }
  }

  return *left;
}

// class operator overloading
Matrix2D& Matrix3D::operator[](uint32_t index) {
  if (index < row_) {
    return pointer_[index];
  }

  return pointer_[0];
}

Matrix3D& Matrix3D::operator+=(const Matrix3D& right) {
  return __doapl(this, right);
}

Matrix3D& Matrix3D::operator-=(const Matrix3D& right) {
  return __doami(this, right);
}

Matrix3D& Matrix3D::operator*=(double right) {
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] *= right;
  }

  return *this;
}

Matrix3D& Matrix3D::operator/=(double right) {
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] /= right;
  }

  return *this;
}

// global operator overloading
// add
Matrix3D operator+(const Matrix3D& x, const Matrix3D& y) {
  uint32_t row = x.GetRow();
  uint32_t column = x.GetColumn();
  uint32_t length = x.GetLength();
  Matrix2D* x_pointer = x.GetPointer();
  Matrix2D* y_pointer = y.GetPointer();

  if (row == y.GetRow() && column == y.GetColumn() && length == y.GetLength()) {
    Matrix3D result(row, column, length);
    for (uint32_t i = 0; i < row; i++) {
      result[i] = x_pointer[i] + y_pointer[i];
    }
    return result;
  }

  return Matrix3D();
}

// subtract
Matrix3D operator-(const Matrix3D& x, const Matrix3D& y) {
  uint32_t row = x.GetRow();
  uint32_t column = x.GetColumn();
  uint32_t length = x.GetLength();
  Matrix2D* x_pointer = x.GetPointer();
  Matrix2D* y_pointer = y.GetPointer();

  if (row == y.GetRow() && column == y.GetColumn() && length == y.GetLength()) {
    Matrix3D result(row, column, length);
    for (uint32_t i = 0; i < row; i++) {
      result[i] = x_pointer[i] - y_pointer[i];
    }
    return result;
  }

  return Matrix3D();
}

// multiply
Matrix3D operator*(const Matrix3D& x, double y) {
  uint32_t row = x.GetRow();
  Matrix2D* x_pointer = x.GetPointer();

  Matrix3D result(row, x.GetColumn(), x.GetLength());
  for (uint32_t i = 0; i < row; i++) {
    result[i] = x_pointer[i] * y;
  }

  return result;
}

Matrix3D operator*(double x, const Matrix3D& y) {
  uint32_t row = y.GetRow();
  Matrix2D* y_pointer = y.GetPointer();

  Matrix3D result(row, y.GetColumn(), y.GetLength());
  for (uint32_t i = 0; i < row; i++) {
    result[i] = x * y_pointer[i];
  }

  return result;
}

// divide
Matrix3D operator/(const Matrix3D& x, double y) {
  uint32_t row = x.GetRow();
  Matrix2D* x_pointer = x.GetPointer();

  Matrix3D result(row, x.GetColumn(), x.GetLength());
  for (uint32_t i = 0; i < row; i++) {
    result[i] = x_pointer[i] / y;
  }

  return result;
}

// equal
bool operator==(const Matrix3D& x, const Matrix3D& y) {
  uint32_t row = x.GetRow();
  Matrix2D* x_pointer = x.GetPointer();
  Matrix2D* y_pointer = y.GetPointer();

  if (row == y.GetRow() && x.GetColumn() == y.GetColumn() &&
      x.GetLength() == y.GetLength()) {
    for (uint32_t i = 0; i < row; i++) {
      if (x_pointer[i] != y_pointer[i]) {
        return false;
      }
    }
    return true;
  }

  return false;
}

// not equal
bool operator!=(const Matrix3D& x, const Matrix3D& y) {
  uint32_t row = x.GetRow();
  Matrix2D* x_pointer = x.GetPointer();
  Matrix2D* y_pointer = y.GetPointer();

  if (row == y.GetRow() && x.GetColumn() == y.GetColumn() &&
      x.GetLength() == y.GetLength()) {
    for (uint32_t i = 0; i < row; i++) {
      if (x_pointer[i] != y_pointer[i]) {
        return true;
      }
    }
    return false;
  }

  return true;
}

// output
std::ostream& operator<<(std::ostream& os, const Matrix3D& matrix_3d) {
  uint32_t row = matrix_3d.GetRow();

  os << '[' << std::endl << matrix_3d.GetPointer()[0];

  for (uint32_t i = 1; i < row; i++) {
    os << ',' << std::endl << std::endl;
    os << matrix_3d.GetPointer()[i];
  }

  return os << std::endl << ']';
}

}  // namespace matrix
