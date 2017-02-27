#include "logic/ast-var.hh"
#include <cassert>

namespace logic
{

  ASTVar::ASTVar(const Token& token)
    : AST(token, {})
  {
    assert(token.type == Token::Type::ID);
  }

  AST* ASTVar::clone() const
  {
    return new ASTVar(token_);
  }

  void ASTVar::accept(Visitor& visitor)
  {
    visitor.visit(*this);
  }

  const std::string& ASTVar::value_get() const
  {
    return token_.value;
  }
  
  std::string& ASTVar::value_get()
  {
    return token_.value;
  }
  
}
