#include "logic/lexer.hh"
#include <cctype>
#include <stdexcept>

namespace logic
{
  Lexer::Lexer(std::istream& is)
    : is_(is)
    , token_(read_())
  {}

  Token Lexer::peek() const
  {
    return token_;
  }

  bool Lexer::is_eof() const
  {
    return token_.type == Token::Type::END;
  }

  Token Lexer::next()
  {
    Token res = token_;
    if (!is_eof())
      token_ = read_();
    return res;
  }


  Token Lexer::eat(Token::Type type)
  {
    if (token_.type != type)
      throw std::runtime_error{"Unexpected token '" + token_.value + '"'};
    return next();
  }

  Token Lexer::read_()
  {
    while (true)
      {
        int c = is_.peek();
        if (c != ' ' && c != '\n' && c != '\t')
          break;
        is_.get();
      }

    int c = is_.peek();
    if (c == EOF)
      return Token{"", Token::Type::END};

    if (isalpha(c))
      return read_id_();
    else
      return read_sym_();
  }

  Token Lexer::read_id_()
  {
    std::string value;
    //std::cout << "id: " << value << "\n";

    while (true)
      {
        int c = is_.peek();
        if (!isalnum(c))
          break;
        value.push_back(is_.get());

        //std::cout << "id: " << value << "\n";
      }

    if (value == "True")
      return Token{value, Token::Type::TRUE};
    if (value == "False")
      return Token{value, Token::Type::FALSE};

    return Token{value, Token::Type::ID};
  }

  Token Lexer::read_sym_()
  {
    std::string value;
    //std::cout << "sym: " << value << "\n";

    while (true)
      {
        int c = is_.peek();
        if (c == EOF)
          break;
        value.push_back(is_.get());

        //std::cout << "sym: " << value << "\n";

        if (value == "(")
          return Token{value, Token::Type::LPAREN};
        if (value == ")")
          return Token{value, Token::Type::RPAREN};
        if (value == "!")
          return Token{value, Token::Type::NOT};
        if (value == "&")
          return Token{value, Token::Type::AND};
        if (value == "|")
          return Token{value, Token::Type::OR};
        if (value == "=>")
          return Token{value, Token::Type::IMPLIES};
        if (value == "<=>")
          return Token{value, Token::Type::IFF};
      }

    throw std::runtime_error{"Lexer: invalid token '" + value + "'"};
  }
}
