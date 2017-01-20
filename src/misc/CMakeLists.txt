cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -fPIC")

set(SRC
  parse-error.cc
)

add_library(misc_obj OBJECT ${SRC})
