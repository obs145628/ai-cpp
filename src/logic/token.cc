#include "logic/token.hh"

namespace logic
{

  Token::Token(const std::string& value, Type type)
    : value(value)
    , type(type)
  {}

  Token::Token(const Token& token)
    : value(token.value)
    , type(token.type)
  {}
  
  Token& Token::operator=(const Token& token)
  {
    value = token.value;
    type = token.type;
    return *this;
  }


  std::ostream& operator<<(std::ostream& os, const Token& tk)
  {
    auto it = Token::TYPES_NAMES.find(tk.type);
    return os << it->second << " (" << tk.value << ")";
  }

  const std::map<Token::Type, std::string> Token::TYPES_NAMES =
    {
      {Type::LPAREN, "LPAREN"},
      {Type::RPAREN, "RPAREN"},
      {Type::TRUE, "TRUE"},
      {Type::FALSE, "FALSE"},
      {Type::ID, "ID"},
      {Type::NOT, "NOT"},
      {Type::AND, "AND"},
      {Type::OR, "OR"},
      {Type::IMPLIES, "IMPLIES"},
      {Type::IFF, "IFF"},
      {Type::END, "EOF"},
    };

}
