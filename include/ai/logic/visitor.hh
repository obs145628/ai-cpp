#pragma once

namespace logic
{

  class AST;
  class ASTAnd;
  class ASTConst;
  class ASTIff;
  class ASTImplies;
  class ASTNot;
  class ASTOr;
  class ASTVar;

  class Visitor
  {

  public:

    Visitor();
    virtual ~Visitor();

    void operator()(AST& ast);

    virtual void visit(ASTAnd& ast) = 0;
    virtual void visit(ASTConst& ast) = 0;
    virtual void visit(ASTIff& ast) = 0;
    virtual void visit(ASTImplies& ast) = 0;
    virtual void visit(ASTNot& ast) = 0;
    virtual void visit(ASTOr& ast) = 0;
    virtual void visit(ASTVar& ast) = 0;
    
  };
}
