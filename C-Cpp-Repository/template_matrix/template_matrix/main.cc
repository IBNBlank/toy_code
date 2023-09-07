/****************************************************************
 * Copyright 2021 HUST Control Science Innovation Base.
 * All rights reserved.
 * Author : Dong Zhaorui 847235539@qq.com
 * Date   : 2021-12-02
 ****************************************************************/

#include <iostream>

#include "template_matrix/complex.hpp"
#include "template_matrix/matrix.hpp"

using template_matrix::Complex;
using template_matrix::Matrix1D;
using template_matrix::Matrix2D;
using template_matrix::Matrix3D;

int main(int argc, char const* argv[]) {
  uint32_t row = 3;
  uint32_t column = 3;
  uint32_t length = 3;

  Matrix1D<double, 2> matrix_1d_test = {1.0, 2.0};
  Matrix2D<double, 2, 2> matrix_2d_test = {{1.0, 2.0}, {3.0, 4.0}};
  Matrix3D<double, 2, 2, 2> matrix_3d_test = {{{1.0, 2.0}, {3.0, 4.0}},
                                              {{5.0, 6.0}, {7.0, 8.0}}};

  std::cout << "Matrix1D {} : " << matrix_1d_test << std::endl << std::endl;
  std::cout << "Matrix2D {} : " << matrix_2d_test << std::endl << std::endl;
  std::cout << "Matrix3D {} : " << matrix_3d_test << std::endl << std::endl;

  Matrix3D<Complex<double>, 3, 3, 3> matrix_3d;

  Matrix2D<Complex<double>, 3, 3>* matrix2d_list;
  matrix2d_list = new Matrix2D<Complex<double>, 3, 3>[row];
  for (uint32_t i = 0; i < row; i++) {
    Matrix1D<Complex<double>, 3>* temp_1d_pointer =
        matrix2d_list[i].GetPointer();
    for (uint32_t j = 0; j < column; j++) {
      Complex<double>* temp_element_pointer = temp_1d_pointer[j].GetPointer();
      for (uint32_t k = 0; k < length; k++) {
        uint32_t index = (i * column + j) * length + k;
        matrix_3d[i][j][k] = Complex<double>(index, index);
        temp_element_pointer[k] = Complex<double>(1.0, 1.0);
      }
    }
  }

  std::cout << "Matrix3D [] : " << matrix_3d << std::endl << std::endl;

  Matrix3D<Complex<double>, 3, 3, 3> matrix_right(matrix2d_list);
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

  Matrix3D<Complex<double>, 3, 3, 3> matrix_3d_1(matrix_3d);
  std::cout << "Matrix3D cpy_ctor : " << matrix_3d_1 << std::endl << std::endl;

  Matrix3D<Complex<double>, 3, 3, 3> matrix_3d_2;
  matrix_3d_2 = matrix_3d;
  std::cout << "Matrix3D = : " << matrix_3d_2 << std::endl << std::endl;

  return 0;
}
