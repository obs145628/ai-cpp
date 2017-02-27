#pragma once

#include "lexer.hh"

namespace logic
{

  class AST;

  class Parser
  {
  public:
    Parser(std::istream& is);

    /**
     * Parse and build an AST from the input streamn
     * S -> exp EOF
     */
    AST* parse();

  private:
    Lexer lex_;

    /**
     * exp -> bic
     */
    AST* exp_();

    /**
     * bic -> impl (IFF impl)*
     */
    AST* bic_();

    /**
     * impl -> disj (IMPLIES disj)*
     */
    AST* impl_();

    /**
     * disj -> conj (OR conj)*
     */
    AST* disj_();

    /**
     * conj -> neg (AND neg)*
     */
    AST* conj_();

    /**
     * neg -> atom_ | NOT neg
     */
    AST* neg_();

    /**
     * atom -> TRUE | FALSE | ID | LPAREN exp RPAREN
     */
    AST* atom_();
  };

}
