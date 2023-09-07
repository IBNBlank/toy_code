cmake_minimum_required(VERSION 3.0.2)
project(template_matrix)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/template_matrix
)

add_executable(template_matrix template_matrix/main.cc
)
