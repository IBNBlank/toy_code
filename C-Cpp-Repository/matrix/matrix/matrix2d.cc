/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/
#include "matrix/matrix2d.h"

#include <string.h>

namespace matrix {
// constructor
Matrix2D::Matrix2D(uint32_t row, uint32_t column, const Complex* value_list)
    : row_(row), column_(column) {
  if (row_ == 0 || column_ == 0) {
    row_ = 1;
    column_ = 1;
  }
  pointer_ = new Vector[row_];
  if (value_list) {
    for (uint32_t i = 0; i < row_; i++) {
      pointer_[i] = Vector(column_, value_list + i * column_);
    }
  } else {
    for (uint32_t i = 0; i < row_; i++) {
      pointer_[i] = Vector(column_);
    }
  }
}

// big three
Matrix2D::Matrix2D(const Matrix2D& matrix_2d) {
  row_ = matrix_2d.GetRow();
  column_ = matrix_2d.GetColumn();
  pointer_ = new Vector[row_];
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] = matrix_2d.GetPointer()[i];
  }
}

Matrix2D& Matrix2D::operator=(const Matrix2D& matrix_2d) {
  if (this == &matrix_2d) {
    return *this;
  }

  delete[] pointer_;

  row_ = matrix_2d.GetRow();
  column_ = matrix_2d.GetColumn();
  pointer_ = new Vector[row_];
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] = matrix_2d.GetPointer()[i];
  }

  return *this;
}

// private method
inline Matrix2D& __doapl(Matrix2D* left, const Matrix2D& right) {
  if (left->row_ == right.row_ && left->column_ == right.column_) {
    for (uint32_t i = 0; i < left->row_; i++) {
      left->pointer_[i] += right.pointer_[i];
    }
  }

  return *left;
}

inline Matrix2D& __doami(Matrix2D* left, const Matrix2D& right) {
  if (left->row_ == right.row_ && left->column_ == right.column_) {
    for (uint32_t i = 0; i < left->row_; i++) {
      left->pointer_[i] -= right.pointer_[i];
    }
  }

  return *left;
}

// class operator overloading
Vector& Matrix2D::operator[](uint32_t index) {
  if (index < row_) {
    return pointer_[index];
  }

  return pointer_[0];
}

Matrix2D& Matrix2D::operator+=(const Matrix2D& right) {
  return __doapl(this, right);
}

Matrix2D& Matrix2D::operator-=(const Matrix2D& right) {
  return __doami(this, right);
}

Matrix2D& Matrix2D::operator*=(double right) {
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] *= right;
  }

  return *this;
}

Matrix2D& Matrix2D::operator/=(double right) {
  for (uint32_t i = 0; i < row_; i++) {
    pointer_[i] /= right;
  }

  return *this;
}

// global operator overloading
// add
Matrix2D operator+(const Matrix2D& x, const Matrix2D& y) {
  uint32_t row = x.GetRow();
  uint32_t column = x.GetColumn();
  Vector* x_pointer = x.GetPointer();
  Vector* y_pointer = y.GetPointer();

  if (row == y.GetRow() && column == y.GetColumn()) {
    Matrix2D result(row, column);
    for (uint32_t i = 0; i < row; i++) {
      result[i] = x_pointer[i] + y_pointer[i];
    }
    return result;
  }

  return Matrix2D();
}

// subtract
Matrix2D operator-(const Matrix2D& x, const Matrix2D& y) {
  uint32_t row = x.GetRow();
  uint32_t column = x.GetColumn();
  Vector* x_pointer = x.GetPointer();
  Vector* y_pointer = y.GetPointer();

  if (row == y.GetRow() && column == y.GetColumn()) {
    Matrix2D result(row, column);
    for (uint32_t i = 0; i < row; i++) {
      result[i] = x_pointer[i] - y_pointer[i];
    }
    return result;
  }

  return Matrix2D();
}

// multiply
Matrix2D operator*(const Matrix2D& x, const Matrix2D& y) {
  uint32_t row = x.GetRow();
  uint32_t column = y.GetColumn();
  Vector* x_pointer = x.GetPointer();
  Vector* y_pointer = y.GetPointer();

  if (x.GetColumn() == y.GetRow()) {
    uint32_t multiply_length = y.GetRow();
    Matrix2D result(row, column);
    for (uint32_t i = 0; i < row; i++) {
      for (uint32_t j = 0; j < column; j++) {
        result[i][j] = Complex();
        for (uint32_t k = 0; k < multiply_length; k++) {
          result[i][j] += x_pointer[i][k] * y_pointer[k][j];
        }
      }
    }
    return result;
  }

  return Matrix2D();
}

Matrix2D operator*(const Matrix2D& x, double y) {
  uint32_t row = x.GetRow();
  Vector* x_pointer = x.GetPointer();

  Matrix2D result(row, x.GetColumn());
  for (uint32_t i = 0; i < row; i++) {
    result[i] = x_pointer[i] * y;
  }

  return result;
}

Matrix2D operator*(double x, const Matrix2D& y) {
  uint32_t row = y.GetRow();
  Vector* y_pointer = y.GetPointer();

  Matrix2D result(row, y.GetColumn());
  for (uint32_t i = 0; i < row; i++) {
    result[i] = x * y_pointer[i];
  }

  return result;
}

// divide
Matrix2D operator/(const Matrix2D& x, double y) {
  uint32_t row = x.GetRow();
  Vector* x_pointer = x.GetPointer();

  Matrix2D result(row, x.GetColumn());
  for (uint32_t i = 0; i < row; i++) {
    result[i] = x_pointer[i] / y;
  }

  return result;
}

// equal
bool operator==(const Matrix2D& x, const Matrix2D& y) {
  uint32_t row = x.GetRow();
  Vector* x_pointer = x.GetPointer();
  Vector* y_pointer = y.GetPointer();

  if (row == y.GetRow() && x.GetColumn() == y.GetColumn()) {
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
bool operator!=(const Matrix2D& x, const Matrix2D& y) {
  uint32_t row = x.GetRow();
  Vector* x_pointer = x.GetPointer();
  Vector* y_pointer = y.GetPointer();

  if (row == y.GetRow() && x.GetColumn() == y.GetColumn()) {
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
std::ostream& operator<<(std::ostream& os, const Matrix2D& matrix_2d) {
  uint32_t row = matrix_2d.GetRow();

  os << '[' << matrix_2d.GetPointer()[0];

  for (uint32_t i = 1; i < row; i++) {
    os << ',' << std::endl;
    os << matrix_2d.GetPointer()[i];
  }

  return os << ']';
}

}  // namespace matrix
