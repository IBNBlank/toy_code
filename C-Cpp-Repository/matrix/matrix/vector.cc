/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#include "matrix/vector.h"

#include <string.h>

namespace matrix {
// constructor
Vector::Vector(uint32_t length, const Complex* value_list) : length_(length) {
  if (length_ == 0) {
    length_ = 1;
  }
  pointer_ = new Complex[length_];
  if (value_list) {
    memcpy(pointer_, value_list, length_ * sizeof(Complex));
  }
}

// big three
Vector::Vector(const Vector& vector) {
  length_ = vector.GetLength();
  pointer_ = new Complex[length_];
  memcpy(pointer_, vector.GetPointer(), length_ * sizeof(Complex));
}

Vector& Vector::operator=(const Vector& vector) {
  if (this == &vector) {
    return *this;
  }

  delete[] pointer_;

  length_ = vector.GetLength();
  pointer_ = new Complex[length_];
  memcpy(pointer_, vector.GetPointer(), length_ * sizeof(Complex));

  return *this;
}

// private method
inline Vector& __doapl(Vector* left, const Vector& right) {
  if (left->length_ == right.length_) {
    for (uint32_t i = 0; i < left->length_; i++) {
      left->pointer_[i] += right.pointer_[i];
    }
  }

  return *left;
}

inline Vector& __doami(Vector* left, const Vector& right) {
  if (left->length_ == right.length_) {
    for (uint32_t i = 0; i < left->length_; i++) {
      left->pointer_[i] -= right.pointer_[i];
    }
  }

  return *left;
}

// class operator overloading
Complex& Vector::operator[](uint32_t index) {
  if (index < length_) {
    return pointer_[index];
  }

  return pointer_[0];
}

Vector& Vector::operator+=(const Vector& right) { return __doapl(this, right); }

Vector& Vector::operator-=(const Vector& right) { return __doami(this, right); }

Vector& Vector::operator*=(double right) {
  for (uint32_t i = 0; i < length_; i++) {
    pointer_[i] *= right;
  }

  return *this;
}

Vector& Vector::operator/=(double right) {
  for (uint32_t i = 0; i < length_; i++) {
    pointer_[i] /= right;
  }

  return *this;
}

// global operator overloading
// add
Vector operator+(const Vector& x, const Vector& y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();
  Complex* y_pointer = y.GetPointer();

  if (length == y.GetLength()) {
    Vector result(length, x_pointer);
    for (uint32_t i = 0; i < length; i++) {
      result[i] += y_pointer[i];
    }
    return result;
  }

  return Vector();
}

// subtract
Vector operator-(const Vector& x, const Vector& y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();
  Complex* y_pointer = y.GetPointer();

  if (length == y.GetLength()) {
    Vector result(length, x_pointer);
    for (uint32_t i = 0; i < length; i++) {
      result[i] -= y_pointer[i];
    }
    return result;
  }

  return Vector();
}

// multiply
Vector operator*(const Vector& x, const Vector& y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();
  Complex* y_pointer = y.GetPointer();

  if (length == y.GetLength()) {
    Vector result(length, x_pointer);
    for (uint32_t i = 0; i < length; i++) {
      result[i] *= y_pointer[i];
    }
    return result;
  }

  return Vector();
}

Vector operator*(const Vector& x, double y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();

  Vector result(length, x_pointer);
  for (uint32_t i = 0; i < length; i++) {
    result[i] *= y;
  }

  return result;
}

Vector operator*(double x, const Vector& y) {
  uint32_t length = y.GetLength();
  Complex* y_pointer = y.GetPointer();

  Vector result(length, y_pointer);
  for (uint32_t i = 0; i < length; i++) {
    result[i] *= x;
  }

  return result;
}

// divide
Vector operator/(const Vector& x, double y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();

  Vector result(length, x_pointer);
  for (uint32_t i = 0; i < length; i++) {
    result[i] /= y;
  }

  return result;
}

// equal
bool operator==(const Vector& x, const Vector& y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();
  Complex* y_pointer = y.GetPointer();

  if (length == y.GetLength()) {
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
bool operator!=(const Vector& x, const Vector& y) {
  uint32_t length = x.GetLength();
  Complex* x_pointer = x.GetPointer();
  Complex* y_pointer = y.GetPointer();

  if (length == y.GetLength()) {
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
std::ostream& operator<<(std::ostream& os, const Vector& vector) {
  uint32_t length = vector.GetLength();

  os << '[' << vector.GetPointer()[0];

  for (uint32_t i = 1; i < length; i++) {
    os << ',';
    os << vector.GetPointer()[i];
  }

  return os << ']';
}

}  // namespace matrix
