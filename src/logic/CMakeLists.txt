set(CMAKE_CXX_FLAGS "${CXX_BASE_FLAGS} -fPIC")

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
