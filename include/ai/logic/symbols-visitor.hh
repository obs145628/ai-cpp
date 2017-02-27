#pragma once

#include "visitor.hh"
#include <set>
#include <string>

namespace logic
{
  class SymbolsVisitor : public Visitor
  {
  public:

    static std::set<std::string> get(AST& ast);

    virtual void visit(ASTAnd& ast) override;
    virtual void visit(ASTConst& ast) override;
    virtual void visit(ASTIff& ast) override;
    virtual void visit(ASTImplies& ast) override;
    virtual void visit(ASTNot& ast) override;
    virtual void visit(ASTOr& ast) override;
    virtual void visit(ASTVar& ast) override;

  private:
    std::set<std::string> res_;
    
  };
}
