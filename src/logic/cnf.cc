#include "logic/cnf.hh"
#include <cassert>
#include "logic/ast-and.hh"
#include "logic/ast-const.hh"
#include "logic/ast-iff.hh"
#include "logic/ast-implies.hh"
#include "logic/ast-not.hh"
#include "logic/ast-or.hh"
#include "logic/ast-var.hh"

namespace logic
{
  AST* CNF::build(AST& ast)
  {
    CNF builder;
    AST* res = builder.apply(ast, 1);
    res = builder.apply(*res, 2);
    res = builder.apply(*res, 3);
    res = builder.apply(*res, 4);
    return res;
  }

  AST* CNF::apply(AST& ast, int type)
  {
    type_ = type;
    ast.accept(*this);

    if (res_ != &ast && type >= 3)
      return apply(*res_, type);
    else
      return res_;
  }

  void CNF::visit(ASTAnd& ast)
  {
    build_nodes_(ast);
    res_ = &ast;
  }
  
  void CNF::visit(ASTConst& ast)
  {
    build_nodes_(ast);
    res_ = &ast;
  }
  
  void CNF::visit(ASTIff& ast)
  {
    build_nodes_(ast);

    if (type_ == 1)
      {
        auto children = ast.detach();
        AST* a = children[0];
        AST* b = children[1];
        AST* a2 = a->clone();
        AST* b2 = b->clone();

        AST* left = new ASTImplies(Token("=>", Token::Type::IMPLIES), a, b);
        AST* right = new ASTImplies(Token("=>", Token::Type::IMPLIES), b2, a2);
        delete &ast;
        res_ = new ASTAnd(Token("&", Token::Type::AND), left, right);
      }

    else
      res_ = &ast;
  }
  
  void CNF::visit(ASTImplies& ast)
  {
    build_nodes_(ast);

    if (type_ == 2)
      {
        auto children = ast.detach();
        AST* a = children[0];
        AST* b = children[1];

        AST* na = new ASTNot(Token("!", Token::Type::NOT), a);
        delete &ast;
        res_ = new ASTOr(Token("|", Token::Type::OR), na, b);
      }

    else
      res_ = &ast;
  }
  
  void CNF::visit(ASTNot& ast)
  {
    build_nodes_(ast);

    if (type_ == 3)
      {
        AST* temp = ast.children_get()[0];
        if (dynamic_cast<ASTNot*>(temp))
          {
            auto children = ast.detach();
            AST* a = children[0];
            children = a->detach();
            delete &ast;
            delete a;
            res_ = children[0];
          }

        else if (dynamic_cast<ASTAnd*>(temp))
          {
            auto children = ast.detach();
            AST* c = children[0];
            children = c->detach();
            AST* a = children[0];
            AST* b = children[1];
            AST* na = new ASTNot(Token("!", Token::Type::NOT), a);
            AST* nb = new ASTNot(Token("!", Token::Type::NOT), b);
            delete &ast;
            delete c;
            res_ = new ASTOr(Token("|", Token::Type::OR), na, nb);
          }

        else if (dynamic_cast<ASTOr*>(temp))
          {
            auto children = ast.detach();
            AST* c = children[0];
            children = c->detach();
            AST* a = children[0];
            AST* b = children[1];
            AST* na = new ASTNot(Token("!", Token::Type::NOT), a);
            AST* nb = new ASTNot(Token("!", Token::Type::NOT), b);
            delete &ast;
            delete c;
            res_ = new ASTAnd(Token("&", Token::Type::AND), na, nb);
          }

        else
          res_ = &ast;
      }

    else
      res_ = &ast;
  }
  
  void CNF::visit(ASTOr& ast)
  {
    build_nodes_(ast);

    if (type_ == 4)
      {
        AST* ltemp = ast.children_get()[0];
        AST* rtemp = ast.children_get()[1];

        if (dynamic_cast<ASTAnd*>(ltemp))
          {
            auto children = ast.detach();
            AST* ab = children[0];
            AST* c = children[1];
            AST* c2 = c->clone();
            children = ab->detach();
            AST* a = children[0];
            AST* b = children[1];

            delete &ast;
            delete ab;
            AST* ac = new ASTOr(Token("|", Token::Type::OR), a, c);
            AST* bc = new ASTOr(Token("|", Token::Type::OR), b, c2);
            res_ = new ASTAnd(Token("&", Token::Type::AND), ac, bc);
          }

        else if (dynamic_cast<ASTAnd*>(rtemp))
          {
            auto children = ast.detach();
            AST* c = children[0];
            AST* ab = children[1];
            AST* c2 = c->clone();
            children = ab->detach();
            AST* a = children[0];
            AST* b = children[1];

            delete &ast;
            delete ab;
            AST* ca = new ASTOr(Token("|", Token::Type::OR), c, a);
            AST* cb = new ASTOr(Token("|", Token::Type::OR), c2, b);
            res_ = new ASTAnd(Token("&", Token::Type::AND), ca, cb);
          }

        else
          res_ = &ast;
      }

    else
      res_ = &ast;
  }
  
  void CNF::visit(ASTVar& ast)
  {
    build_nodes_(ast);
    res_ = &ast;
  }

  void CNF::build_nodes_(AST& ast)
  {
    auto& nodes = ast.children_get();
    for (std::size_t i = 0; i < nodes.size(); ++i)
      nodes[i] = apply(*(nodes[i]), type_);
  }
}
