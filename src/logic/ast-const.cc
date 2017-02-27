#include "logic/ast-const.hh"
#include <cassert>

namespace logic
{

  ASTConst::ASTConst(const Token& token)
    : AST(token, {})
  {
    assert(token.type == Token::Type::TRUE
           || token.type == Token::Type::FALSE);
  }

  AST* ASTConst::clone() const
  {
    return new ASTConst(token_);
  }

  void ASTConst::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }

  bool ASTConst::value_get() const
  {
    return token_.type == Token::Type::TRUE;
  }
  
}
