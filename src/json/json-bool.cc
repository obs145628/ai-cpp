#include "json/json-bool.hh"
#include "misc/parse-error.hh"

JsonBool::JsonBool(bool value)
  : value_(value)
{}

JsonBool::JsonBool(std::istream& is)
{
  read_blanks_(is);
  char c = is.get();

  if (c == 't')
    {
      if (is.get() != 'r'
          || is.get() != 'u'
          || is.get() != 'e')
        throw ParseError("invalid json bool");
      value_ = true;
    }

  else if (c == 'f')
    {
      if (is.get() != 'a'
          || is.get() != 'l'
          || is.get() != 's'
          || is.get() != 'e')
        throw ParseError("invalid json bool");
      value_ = false;
    }

  else
    throw ParseError("invalid json bool");
}

Json* JsonBool::clone() const
{
  return new JsonBool(value_);
}

Json::Type JsonBool::type_get() const
{
  return Json::Type::BOOL;
}

void JsonBool::write(std::ostream& os, int, int) const
{
  if (value_)
    os << "true";
  else
    os << "false";
}

bool JsonBool::value_get() const
{
  return value_;
}

void JsonBool::value_set(bool value)
{
  value_ = value;
}
