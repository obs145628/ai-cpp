#pragma once

#include "ast.hh"

namespace logic
{
  class ASTVar : public AST
  {

  public:

    ASTVar(const Token& token);

    virtual AST* clone() const override;
    virtual void accept(Visitor& visitor) override;

    const std::string& value_get() const;
    std::string& value_get();

    
  };
}
