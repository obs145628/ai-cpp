#pragma once

#include "visitor.hh"

namespace logic
{
  class CNF : public Visitor
  {
  public:

    /**
     * Transform an ast into a new ast in CNP Form (Conjonctive Normal Form)
     * (. | . | .) & (. | . | .) & (. | . | .) & ...
     * All memory management is done
     * 1) Replace every 'a <=> b' by '(a => b) & (b => a)'
     * 2) Replace every 'a => b' by '!a | b'
     * 3) Replaces every:
     *     - '!!a' by 'a'
     *     - '!(a & b)' by '!a | !b'
     *     - '!(a | b)' by '!a & !b'
     * 4) Distribute | over &
     */
    static AST* build(AST& ast);

    AST* apply(AST& ast, int type);

    virtual void visit(ASTAnd& ast) override;
    virtual void visit(ASTConst& ast) override;
    virtual void visit(ASTIff& ast) override;
    virtual void visit(ASTImplies& ast) override;
    virtual void visit(ASTNot& ast) override;
    virtual void visit(ASTOr& ast) override;
    virtual void visit(ASTVar& ast) override;

  private:
    int type_;
    AST* res_;

    void build_nodes_(AST& ast);
    
  };
}
