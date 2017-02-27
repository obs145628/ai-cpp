#pragma once

#include "ast.hh"

namespace logic
{
  class ASTBin : public AST
  {

  public:

    ASTBin(const Token& token, AST* left, AST* right);

    const AST& left_get() const;
    AST& left_get();
    const AST& right_get() const;
    AST& right_get();

    
  };
}
