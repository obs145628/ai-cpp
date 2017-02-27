#pragma once

#include <iostream>
#include "token.hh"

namespace logic
{

  class Lexer
  {
  public:
    Lexer(std::istream& is);

    bool is_eof() const;

    Token peek() const;
    Token next();

    Token eat(Token::Type type);

  private:
    std::istream& is_;
    Token token_;

    Token read_();
    Token read_id_();
    Token read_sym_();
  };

}
