cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -fPIC")

set(SRC
  dot-tree.cc
)

add_library(graph_obj OBJECT ${SRC})
