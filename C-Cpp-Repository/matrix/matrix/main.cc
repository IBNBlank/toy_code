/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#include <iostream>

#include "matrix/complex.h"
#include "matrix/matrix3d.h"

using matrix::Complex;
using matrix::Matrix3D;

int main(int argc, char const* argv[]) {
  uint32_t row = 3;
  uint32_t column = 3;
  uint32_t length = 3;
  Matrix3D matrix_3d(row, column, length);
  Complex* complex_list;
  complex_list = new Complex[row * column * length];

  for (uint32_t i = 0; i < row; i++) {
    for (uint32_t j = 0; j < column; j++) {
      for (uint32_t k = 0; k < length; k++) {
        uint32_t index = (i * column + j) * length + k;
        matrix_3d[i][j][k] = Complex(index, index);
        complex_list[index] = Complex(1, 1);
      }
    }
  }

  std::cout << "Matrix3D [] : " << matrix_3d << std::endl << std::endl;

  Matrix3D matrix_right(row, column, length, complex_list);
  std::cout << "Matrix3D ctor : " << matrix_right << std::endl << std::endl;

  std::cout << "Matrix3D + : " << matrix_3d + matrix_right << std::endl
            << std::endl;
  std::cout << "Matrix3D - : " << matrix_3d - matrix_right << std::endl
            << std::endl;
  std::cout << "Matrix3D * left : " << 10 * matrix_3d << std::endl << std::endl;
  std::cout << "Matrix3D * right : " << matrix_3d * 10 << std::endl
            << std::endl;
  std::cout << "Matrix3D / : " << matrix_3d / 10 << std::endl << std::endl;

  if (matrix_3d == matrix_3d) {
    std::cout << "Matrix3D == test finish" << std::endl << std::endl;
  } else {
    std::cout << "Matrix3D == test failed" << std::endl << std::endl;
  }

  if (matrix_3d != matrix_right) {
    std::cout << "Matrix3D != test finish" << std::endl << std::endl;
  } else {
    std::cout << "Matrix3D != test failed" << std::endl << std::endl;
  }

  matrix_3d += matrix_right;
  std::cout << "Matrix3D += : " << matrix_3d << std::endl << std::endl;

  matrix_3d -= 2 * matrix_right;
  std::cout << "Matrix3D -= : " << matrix_3d << std::endl << std::endl;

  matrix_3d *= 100;
  std::cout << "Matrix3D *= : " << matrix_3d << std::endl << std::endl;

  matrix_3d /= 10000;
  std::cout << "Matrix3D /= : " << matrix_3d << std::endl << std::endl;

  Matrix3D matrix_3d_1(matrix_3d);
  std::cout << "Matrix3D cpy_ctor : " << matrix_3d_1 << std::endl << std::endl;

  Matrix3D matrix_3d_2;
  matrix_3d_2 = matrix_3d;
  std::cout << "Matrix3D = : " << matrix_3d_2 << std::endl << std::endl;

  return 0;
}
