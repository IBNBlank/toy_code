/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#ifndef TEMPLATE_MATRIX_MATRIX_HPP_
#define TEMPLATE_MATRIX_MATRIX_HPP_

#include <iostream>

namespace template_matrix {

template <class T, uint32_t length = 0>
class Matrix1D {
 public:
  // constructor
  explicit Matrix1D(const T* value_list = 0);
  Matrix1D(const std::initializer_list<T>&);

  // big three
  Matrix1D(const Matrix1D&);
  inline ~Matrix1D() { delete[] pointer_; }
  Matrix1D& operator=(const Matrix1D&);

  // get element
  inline double GetLength() const { return length_; }
  inline T* GetPointer() const { return pointer_; }
  T& operator[](uint32_t);

  // assignment
  Matrix1D& operator=(const T*);
  Matrix1D& operator+=(const Matrix1D&);
  Matrix1D& operator-=(const Matrix1D&);
  Matrix1D& operator*=(double);
  Matrix1D& operator/=(double);

 private:
  uint32_t length_;
  T* pointer_;

  friend inline Matrix1D& __doapl(Matrix1D* left, const Matrix1D& right) {
    if (left->length_ == right.length_) {
      for (uint32_t i = 0; i < left->length_; i++) {
        left->pointer_[i] += right.pointer_[i];
      }
    }

    return *left;
  }

  friend inline Matrix1D& __doami(Matrix1D* left, const Matrix1D& right) {
    if (left->length_ == right.length_) {
      for (uint32_t i = 0; i < left->length_; i++) {
        left->pointer_[i] -= right.pointer_[i];
      }
    }

    return *left;
  }
};

// constructor
template <class T, uint32_t length>
Matrix1D<T, length>::Matrix1D(const T* value_list) : length_(length) {
  if (length_ == 0) {
    length_ = 1;
  }
  pointer_ = new T[length_];
  if (value_list) {
    for (uint32_t i = 0; i < length_; i++) {
      pointer_[i] = value_list[i];
    }
  }
}

template <class T, uint32_t length>
Matrix1D<T, length>::Matrix1D(const std::initializer_list<T>& value_list)
    : length_(length) {
  if (length_ == 0) {
    length_ = 1;
  }
  pointer_ = new T[length_];

  if (value_list.size() >= length_) {
    uint32_t i = 0;
    for (auto item : value_list) {
      pointer_[i] = item;
      i++;
      if (i == length_) {
        break;
      }
    }
  }
}

// big three
template <class T, uint32_t length>
Matrix1D<T, length>::Matrix1D(const Matrix1D<T, length>& vector) {
  length_ = vector.GetLength();
  pointer_ = new T[length_];
  for (uint32_t i = 0; i < length_; i++) {
    pointer_[i] = vector.GetPointer()[i];
  }
}

template <class T, uint32_t length>
Matrix1D<T, length>& Matrix1D<T, length>::operator=(
    const Matrix1D<T, length>& vector) {
  if (this == &vector) {
    return *this;
  }

  delete[] pointer_;
  length_ = vector.GetLength();
  pointer_ = new T[length_];
  for (uint32_t i = 0; i < length_; i++) {
    pointer_[i] = vector.GetPointer()[i];
  }

  return *this;
}

// class operator overloading
template <class T, uint32_t length>
T& Matrix1D<T, length>::operator[](uint32_t index) {
  if (index < length_) {
    return pointer_[index];
  }

  return pointer_[0];
}

template <class T, uint32_t length>
Matrix1D<T, length>& Matrix1D<T, length>::operator=(const T* value_list) {
  if (value_list) {
    delete[] pointer_;
    for (uint32_t i = 0; i < length_; i++) {
      pointer_[i] = value_list[i];
    }
  }

  return *this;
}

template <class T, uint32_t length>
Matrix1D<T, length>& Matrix1D<T, length>::operator+=(
    const Matrix1D<T, length>& right) {
  return __doapl(this, right);
}

template <class T, uint32_t length>
Matrix1D<T, length>& Matrix1D<T, length>::operator-=(
    const Matrix1D<T, length>& right) {
  return __doami(this, right);
}

template <class T, uint32_t length>
Matrix1D<T, length>& Matrix1D<T, length>::operator*=(double right) {
  for (uint32_t i = 0; i < length_; i++) {
    pointer_[i] *= right;
  }

  return *this;
}

template <class T, uint32_t length>
Matrix1D<T, length>& Matrix1D<T, length>::operator/=(double right) {
  for (uint32_t i = 0; i < length_; i++) {
    pointer_[i] /= right;
  }

  return *this;
}

// global operator overloading
// add
template <class T, uint32_t length>
Matrix1D<T, length> operator+(const Matrix1D<T, length>& x,
                              const Matrix1D<T, length>& y) {
  T* x_pointer = x.GetPointer();
  T* y_pointer = y.GetPointer();

  if (length == x.GetLength() && length == y.GetLength()) {
    Matrix1D<T, length> result(x_pointer);
    for (uint32_t i = 0; i < length; i++) {
      result[i] += y_pointer[i];
    }
    return result;
  }

  return Matrix1D<T, length>();
}

// subtract
template <class T, uint32_t length>
Matrix1D<T, length> operator-(const Matrix1D<T, length>& x,
                              const Matrix1D<T, length>& y) {
  T* x_pointer = x.GetPointer();
  T* y_pointer = y.GetPointer();

  if (length == x.GetLength() && length == y.GetLength()) {
    Matrix1D<T, length> result(x_pointer);
    for (uint32_t i = 0; i < length; i++) {
      result[i] -= y_pointer[i];
    }
    return result;
  }

  return Matrix1D<T, length>();
}

// multiply
template <class T, uint32_t length>
Matrix1D<T, length> operator*(const Matrix1D<T, length>& x, double y) {
  T* x_pointer = x.GetPointer();
  Matrix1D<T, length> result(x_pointer);

  if (length == x.GetLength()) {
    for (uint32_t i = 0; i < length; i++) {
      result[i] *= y;
    }
  }

  return result;
}

template <class T, uint32_t length>
Matrix1D<T, length> operator*(double x, const Matrix1D<T, length>& y) {
  T* y_pointer = y.GetPointer();
  Matrix1D<T, length> result(y_pointer);

  if (length == y.GetLength()) {
    for (uint32_t i = 0; i < length; i++) {
      result[i] *= x;
    }
  }

  return result;
}

// divide
template <class T, uint32_t length>
Matrix1D<T, length> operator/(const Matrix1D<T, length>& x, double y) {
  T* x_pointer = x.GetPointer();
  Matrix1D<T, length> result(x_pointer);

  if (length == x.GetLength()) {
    for (uint32_t i = 0; i < length; i++) {
      result[i] /= y;
    }
  }

  return result;
}

// equal
template <class T, uint32_t length>
bool operator==(const Matrix1D<T, length>& x, const Matrix1D<T, length>& y) {
  T* x_pointer = x.GetPointer();
  T* y_pointer = y.GetPointer();

  if (length == x.GetLength() && length == y.GetLength()) {
    for (uint32_t i = 0; i < length; i++) {
      if (x_pointer[i] != y_pointer[i]) {
        return false;
      }
    }
    return true;
  }

  return false;
}

// not equal
template <class T, uint32_t length>
bool operator!=(const Matrix1D<T, length>& x, const Matrix1D<T, length>& y) {
  T* x_pointer = x.GetPointer();
  T* y_pointer = y.GetPointer();

  if (length == x.GetLength() && length == y.GetLength()) {
    for (uint32_t i = 0; i < length; i++) {
      if (x_pointer[i] != y_pointer[i]) {
        return true;
      }
    }
    return false;
  }

  return true;
}

// output
template <class T, uint32_t length>
std::ostream& operator<<(std::ostream& os, const Matrix1D<T, length>& vector) {
  os << '[' << vector.GetPointer()[0];

  if (length == vector.GetLength()) {
    for (uint32_t i = 1; i < length; i++) {
      os << ',';
      os << vector.GetPointer()[i];
    }
  }

  return os << ']';
}

template <class T, uint32_t row = 1, uint32_t column = 1>
using Matrix2D = Matrix1D<Matrix1D<T, column>, row>;

template <class T, uint32_t row = 1, uint32_t column = 1, uint32_t length = 1>
using Matrix3D = Matrix1D<Matrix2D<T, column, length>, row>;

}  // namespace template_matrix

#endif  // TEMPLATE_MATRIX_MATRIX_HPP_
