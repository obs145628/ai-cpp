#pragma once

#include "ast-bin.hh"

namespace logic
{
  class ASTAnd : public ASTBin
  {

  public:

    ASTAnd(const Token& token, AST* left, AST* right);
    
    virtual AST* clone() const override;
    virtual void accept(Visitor& visitor) override;

    
  };
}
