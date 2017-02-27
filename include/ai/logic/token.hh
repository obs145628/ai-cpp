#pragma once

#include <iostream>
#include <map>
#include <string>

namespace logic
{

  struct Token
  {
    enum class Type
      {
        LPAREN,   // '('
        RPAREN,   // ')'
        TRUE,     // 'True'
        FALSE,    // 'False'
        ID,       // /^[a-zA-z][a-zA-Z0-9]+$/
        NOT,      // '!'
        AND,      // '&'
        OR,       // '|'
        IMPLIES,  // '=>'
        IFF,      // '<=>'
        END       // <EOF>
      };

    Token(const std::string& value, Type type);
    Token(const Token& token);
    Token& operator=(const Token& token);

    std::string value;
    Type type;

    static const std::map<Type, std::string> TYPES_NAMES;
  };

  std::ostream& operator<<(std::ostream& os, const Token& tk);
  
}
