#pragma once

#include "visitor.hh"
#include "model.hh"

namespace logic
{
  class EvalVisitor : public Visitor
  {
  public:

    static bool eval(AST& ast, const Model& model);

    EvalVisitor(const Model& model);

    bool operator()(AST& ast);

    virtual void visit(ASTAnd& ast) override;
    virtual void visit(ASTConst& ast) override;
    virtual void visit(ASTIff& ast) override;
    virtual void visit(ASTImplies& ast) override;
    virtual void visit(ASTNot& ast) override;
    virtual void visit(ASTOr& ast) override;
    virtual void visit(ASTVar& ast) override;

  private:
    const Model& model_;
    bool value_;
    
  };
}
