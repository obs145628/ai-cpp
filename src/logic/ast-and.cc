#include "logic/ast-and.hh"
#include <cassert>

namespace logic
{

  ASTAnd::ASTAnd(const Token& token, AST* left, AST* right)
    : ASTBin(token, left, right)
  {
    assert(token.type == Token::Type::AND);
  }

  AST* ASTAnd::clone() const
  {
    return new ASTAnd(token_, left_get().clone(), right_get().clone());
  }

  void ASTAnd::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }
  
}
