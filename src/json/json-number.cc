#include "json/json-number.hh"
#include <sstream>
#include "misc/parse-error.hh"

JsonNumber::JsonNumber(long n)
  : is_int_(true)
  , ival_(n)
{}

JsonNumber::JsonNumber(double n)
  : is_int_(false)
  , dval_(n)
{}

JsonNumber::JsonNumber(std::istream& is)
{
  read_blanks_(is);

  std::ostringstream ss;
  while (true)
    {
      if (!is.good())
        break;
      char c = is.peek();
      if (c != '.' && c != '-' && (c < '0' || c > '9'))
        break;
      ss << c;
      is.get();
    }
  std::string token = ss.str();

  if (token.empty() ||
      (token[0] != '-' && (token[0] < '0' || token[0] > '9')))
    throw ParseError("invalid json number");

  if (token.find('.') == std::string::npos)
    {
      const char* begin = token.c_str();
      char* end;
      long val = strtol(begin, &end, 10);
      std::size_t len = end - begin;
      if (len != token.size())
        throw ParseError("invalid json number");
      int_set(val);
    }

  else
    {
      const char* begin = token.c_str();
      char* end;
      double val = strtod(begin, &end);
      std::size_t len = end - begin;
      if (len != token.size())
        throw ParseError("invalid json number");
      double_set(val);
    }

}


Json* JsonNumber::clone() const
{
  if (is_int_)
    return new JsonNumber(ival_);
  else
    return new JsonNumber(dval_);
}
  
Json::Type JsonNumber::type_get() const
{
  return Json::Type::NUMBER;
}

void JsonNumber::write(std::ostream& os, int, int) const
{
  if (is_int_)
    os << ival_;
  else
    os << dval_;
}


bool JsonNumber::is_int() const
{
  return is_int_;
}

long JsonNumber::int_get() const
{
  if (is_int_)
    return ival_;
  else
    return dval_;
}

double JsonNumber::double_get() const
{
  if (is_int_)
    return ival_;
  else
    return dval_;
}

void JsonNumber::int_set(long n)
{
  is_int_ = true;
  ival_ = n;
}

void JsonNumber::double_set(double n)
{
  is_int_ = false;
  dval_ = n;
}
