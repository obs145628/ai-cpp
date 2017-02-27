#pragma once

#include "ast-bin.hh"

namespace logic
{
  class ASTIff : public ASTBin
  {

  public:

    ASTIff(const Token& token, AST* left, AST* right);

    virtual AST* clone() const override;
    virtual void accept(Visitor& visitor) override;

    
  };
}
