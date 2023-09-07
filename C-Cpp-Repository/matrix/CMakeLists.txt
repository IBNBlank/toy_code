cmake_minimum_required(VERSION 3.0.2)
project(matrix)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/matrix
)

add_executable(matrix matrix/main.cc
  matrix/complex.cc
  matrix/vector.cc
  matrix/matrix2d.cc
  matrix/matrix3d.cc
)
