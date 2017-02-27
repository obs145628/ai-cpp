#pragma once

#include "ast.hh"

namespace logic
{
  class ASTNot : public AST
  {

  public:

    ASTNot(const Token& token, AST* right);

    virtual AST* clone() const override;
    virtual void accept(Visitor& visitor) override;

    const AST& right_get() const;
    AST& right_get();

    
  };
}
