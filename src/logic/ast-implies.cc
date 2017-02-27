#include "logic/ast-implies.hh"
#include <cassert>

namespace logic
{
  ASTImplies::ASTImplies(const Token& token, AST* left, AST* right)
    : ASTBin(token, left, right)
  {
    assert(token.type == Token::Type::IMPLIES);
  }

  AST* ASTImplies::clone() const
  {
    return new ASTImplies(token_, left_get().clone(), right_get().clone());
  }

  void ASTImplies::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }
}
