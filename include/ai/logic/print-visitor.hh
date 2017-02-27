#pragma once

#include "visitor.hh"
#include <iostream>

namespace logic
{
  class PrintVisitor : public Visitor
  {
  public:

    static void print(std::ostream& os, AST& ast);

    PrintVisitor(std::ostream& os);

    virtual void visit(ASTAnd& ast) override;
    virtual void visit(ASTConst& ast) override;
    virtual void visit(ASTIff& ast) override;
    virtual void visit(ASTImplies& ast) override;
    virtual void visit(ASTNot& ast) override;
    virtual void visit(ASTOr& ast) override;
    virtual void visit(ASTVar& ast) override;

  private:
    std::ostream& os_;
    
  };
}
