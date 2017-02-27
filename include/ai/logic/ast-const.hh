#pragma once

#include "ast.hh"

namespace logic
{
  class ASTConst : public AST
  {

  public:

    ASTConst(const Token& token);

    virtual AST* clone() const override;
    virtual void accept(Visitor& visitor) override;

    bool value_get() const;

    
  };
}
