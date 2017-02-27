#include "logic/parser.hh"
#include "logic/ast-and.hh"
#include "logic/ast-const.hh"
#include "logic/ast-iff.hh"
#include "logic/ast-implies.hh"
#include "logic/ast-not.hh"
#include "logic/ast-or.hh"
#include "logic/ast-var.hh"

namespace logic
{

  Parser::Parser(std::istream& is)
    : lex_(is)
  {}

  AST* Parser::parse()
  {
    auto res = exp_();
    lex_.eat(Token::Type::END);
    return res;
  }

  AST* Parser::exp_()
  {
    return bic_();
  }

  AST* Parser::bic_()
  {
    auto res = impl_();
    while (lex_.peek().type == Token::Type::IFF)
      {
        auto token = lex_.next();
        res = new ASTIff(token, res, impl_()); 
      }

    return res;
  }

  AST* Parser::impl_()
  {
    auto res = disj_();
    while (lex_.peek().type == Token::Type::IMPLIES)
      {
        auto token = lex_.next();
        res = new ASTImplies(token, res, disj_()); 
      }

    return res;
  }

  AST* Parser::disj_()
  {
    auto res = conj_();
    while (lex_.peek().type == Token::Type::OR)
      {
        auto token = lex_.next();
        res = new ASTOr(token, res, conj_()); 
      }

    return res;
  }

  AST* Parser::conj_()
  {
    auto res = neg_();
    while (lex_.peek().type == Token::Type::AND)
      {
        auto token = lex_.next();
        res = new ASTAnd(token, res, neg_()); 
      }

    return res;
  }


  AST* Parser::neg_()
  {
    if (lex_.peek().type == Token::Type::NOT)
      {
        auto token = lex_.next();
        return new ASTNot(token, neg_());
      }

    else
      return atom_();
  }

  /**
   * atom -> TRUE | FALSE | ID | LPAREN exp RPAREN
   */
  AST* Parser::atom_()
  {
    if (lex_.peek().type == Token::Type::TRUE)
      return new ASTConst(lex_.next());

    else if (lex_.peek().type == Token::Type::FALSE)
      return new ASTConst(lex_.next());

    else if (lex_.peek().type == Token::Type::ID)
      return new ASTVar(lex_.next());

    else
      {
        lex_.eat(Token::Type::LPAREN);
        auto res = exp_();
        lex_.eat(Token::Type::RPAREN);
        return res;
      }
  }
}
