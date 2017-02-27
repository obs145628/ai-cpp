#include "logic/ast-bin.hh"

namespace logic
{

  ASTBin::ASTBin(const Token& token, AST* left, AST* right)
    : AST(token, {left, right})
  {}

  const AST& ASTBin::left_get() const
  {
    return child_get(0);
  }
  
  AST& ASTBin::left_get()
  {
    return child_get(0);
  }
  
  const AST& ASTBin::right_get() const
  {
    return child_get(1);
  }
  
  AST& ASTBin::right_get()
  {
    return child_get(1);
  }
  
}
