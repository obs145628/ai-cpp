#include "logic/eval-visitor.hh"
#include "logic/ast-and.hh"
#include "logic/ast-const.hh"
#include "logic/ast-iff.hh"
#include "logic/ast-implies.hh"
#include "logic/ast-not.hh"
#include "logic/ast-or.hh"
#include "logic/ast-var.hh"

namespace logic
{
  bool EvalVisitor::eval(AST& ast, const Model& model)
  {
    EvalVisitor evaluer(model);
    return evaluer(ast);
  }

  bool EvalVisitor::operator()(AST& ast)
  {
    ast.accept(*this);
    return value_;
  }

  EvalVisitor::EvalVisitor(const Model& model)
    : model_(model)
  {}

  void EvalVisitor::visit(ASTAnd& ast)
  {
    value_ = (*this)(ast.left_get()) && (*this)(ast.right_get());
  }
  
  void EvalVisitor::visit(ASTConst& ast)
  {
    value_ = ast.value_get();
  }
  
  void EvalVisitor::visit(ASTIff& ast)
  {
    value_ = (*this)(ast.left_get()) == (*this)(ast.right_get());
  }
  
  void EvalVisitor::visit(ASTImplies& ast)
  {
    value_ = !(*this)(ast.left_get()) | (*this)(ast.right_get());
  }
  
  void EvalVisitor::visit(ASTNot& ast)
  {
    value_ = !(*this)(ast.right_get());
  }
  
  void EvalVisitor::visit(ASTOr& ast)
  {
    value_ = (*this)(ast.left_get()) || (*this)(ast.right_get());
  }
  
  void EvalVisitor::visit(ASTVar& ast)
  {
    value_ = model_.var_get(ast.value_get());
  }
}
