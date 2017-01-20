cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14")

set(SRC
  main.cc
)

add_library(obs_tests_obj OBJECT ${SRC})
