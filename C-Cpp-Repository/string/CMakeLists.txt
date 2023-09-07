cmake_minimum_required(VERSION 3.0.2)
project(my_string)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/my_string
)

add_executable(my_string my_string/main.cc
  my_string/my_string.cc
)
