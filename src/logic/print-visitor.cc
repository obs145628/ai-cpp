#include "logic/print-visitor.hh"
#include "logic/ast-and.hh"
#include "logic/ast-const.hh"
#include "logic/ast-iff.hh"
#include "logic/ast-implies.hh"
#include "logic/ast-not.hh"
#include "logic/ast-or.hh"
#include "logic/ast-var.hh"

namespace logic
{

  void PrintVisitor::print(std::ostream& os, AST& ast)
  {
    PrintVisitor printer{os};
    printer(ast);
    os << "\n";
  }

  PrintVisitor::PrintVisitor(std::ostream& os)
    : os_(os)
  {}

  void PrintVisitor::visit(ASTAnd& ast)
  {
    os_ << "(";
    (*this)(ast.left_get());
    os_ << " & ";
    (*this)(ast.right_get());
    os_ << ")";
  }

  void PrintVisitor::visit(ASTConst& ast)
  {
    if (ast.value_get())
      os_ << "True";
    else
      os_ << "False";
  }

  void PrintVisitor::visit(ASTIff& ast)
  {
    os_ << "(";
    (*this)(ast.left_get());
    os_ << " <=> ";
    (*this)(ast.right_get());
    os_ << ")";
  }

  void PrintVisitor::visit(ASTImplies& ast)
  {
    os_ << "(";
    (*this)(ast.left_get());
    os_ << " => ";
    (*this)(ast.right_get());
    os_ << ")";
  }

  void PrintVisitor::visit(ASTNot& ast)
  {
    os_ << "!";
    (*this)(ast.right_get());
  }

  void PrintVisitor::visit(ASTOr& ast)
  {
    os_ << "(";
    (*this)(ast.left_get());
    os_ << " | ";
    (*this)(ast.right_get());
    os_ << ")";
  }

  void PrintVisitor::visit(ASTVar& ast)
  {
    os_ << ast.value_get();
  }

}
