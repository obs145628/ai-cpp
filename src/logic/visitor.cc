#include "logic/visitor.hh"
#include "logic/ast.hh"

namespace logic
{
  Visitor::Visitor()
  {}

  Visitor::~Visitor()
  {}

  void Visitor::operator()(AST& ast)
  {
    ast.accept(*this);
  }
}
