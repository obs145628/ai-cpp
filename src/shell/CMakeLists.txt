cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -fPIC")

set(SRC
  command.cc
  date.cc
  grid.cc
  ipc.cc
  shell.cc
  shell-canvas.cc
  shell-drawable.cc
  shell-scene.cc
  shell-sprite.cc
  timer.cc
)

add_library(shell_obj OBJECT ${SRC})
