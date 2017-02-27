#include "logic/ast-iff.hh"
#include <cassert>

namespace logic
{
  ASTIff::ASTIff(const Token& token, AST* left, AST* right)
    : ASTBin(token, left, right)
  {
    assert(token.type == Token::Type::IFF);
  }

  AST* ASTIff::clone() const
  {
    return new ASTIff(token_, left_get().clone(), right_get().clone());
  }

  void ASTIff::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }
}
