cmake_minimum_required(VERSION 3.0.2)
project(ctime)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/ctime
)

add_executable(ctime ctime/main.cc
  ctime/ctime.cc
)