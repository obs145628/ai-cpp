#include "logic/ast-not.hh"
#include <cassert>

namespace logic
{
  ASTNot::ASTNot(const Token& token, AST* right)
    : AST(token, {right})
  {
    assert(token.type == Token::Type::NOT);
  }

  AST* ASTNot::clone() const
  {
    return new ASTNot(token_, right_get().clone());
  }

  void ASTNot::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }

  const AST& ASTNot::right_get() const
  {
    return child_get(0);
  }
  
  AST& ASTNot::right_get()
  {
    return child_get(0);
  }
}
