#pragma once

#include <vector>
#include "token.hh"
#include "visitor.hh"

namespace logic
{
  class AST
  {

  public:
    AST(const Token& token, const std::vector<AST*>& children);
    AST(const AST& ast);
    virtual ~AST();

    virtual AST* clone() const = 0;
    virtual void accept(Visitor& visitor) = 0;

    std::size_t count();
    const AST& child_get(std::size_t i) const;
    AST& child_get(std::size_t i);

    const std::vector<AST*>& children_get() const;
    std::vector<AST*>& children_get();

    const Token& token_get() const;
    Token& token_get();

    std::vector<AST*> detach();

  protected:
    Token token_;
    std::vector<AST*> children_;

    
  };
}
