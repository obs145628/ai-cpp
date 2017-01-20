cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -fPIC")

set(SRC
  cholesky.cc
  cramer.cc
  gauss.cc
  lu.cc
  matrix.cc
  qr.cc
  random.cc
  utils.cc
  vector.cc
  vlist.cc
)

add_library(math_obj OBJECT ${SRC})
