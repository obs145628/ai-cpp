#include "logic/symbols-visitor.hh"

#include "logic/ast-and.hh"
#include "logic/ast-const.hh"
#include "logic/ast-iff.hh"
#include "logic/ast-implies.hh"
#include "logic/ast-not.hh"
#include "logic/ast-or.hh"
#include "logic/ast-var.hh"

namespace logic
{

  std::set<std::string> SymbolsVisitor::get(AST& ast)
  {
    SymbolsVisitor sym;
    sym(ast);
    return sym.res_;
  }

  void SymbolsVisitor::visit(ASTAnd& ast)
  {
    (*this)(ast.left_get());
    (*this)(ast.right_get());
  }

  void SymbolsVisitor::visit(ASTConst&)
  {}

  void SymbolsVisitor::visit(ASTIff& ast)
  {
    (*this)(ast.left_get());
    (*this)(ast.right_get());
  }

  void SymbolsVisitor::visit(ASTImplies& ast)
  {
    (*this)(ast.left_get());
    (*this)(ast.right_get());
  }

  void SymbolsVisitor::visit(ASTNot& ast)
  {
    (*this)(ast.right_get());
  }

  void SymbolsVisitor::visit(ASTOr& ast)
  {
    (*this)(ast.left_get());
    (*this)(ast.right_get());
  }

  void SymbolsVisitor::visit(ASTVar& ast)
  {
    res_.insert(ast.value_get());
  }

}
