#include "logic/ast-or.hh"
#include <cassert>

namespace logic
{
  ASTOr::ASTOr(const Token& token, AST* left, AST* right)
    : ASTBin(token, left, right)
  {
    assert(token.type == Token::Type::OR);
  }

  AST* ASTOr::clone() const
  {
    return new ASTOr(token_, left_get().clone(), right_get().clone());
  }

  void ASTOr::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }
}
