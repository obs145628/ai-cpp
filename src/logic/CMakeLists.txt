cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14 -fPIC")

set(SRC
  ast.cc
  ast-and.cc
  ast-bin.cc
  ast-const.cc
  ast-iff.cc
  ast-implies.cc
  ast-not.cc
  ast-or.cc
  ast-var.cc
  cnf.cc
  eval-visitor.cc
  lexer.cc
  model.cc
  parser.cc
  print-visitor.cc
  propositional-kb.cc
  symbols-visitor.cc
  token.cc
  visitor.cc
)

add_library(logic_obj OBJECT ${SRC})
