#include "json/json-null.hh"
#include "misc/parse-error.hh"

JsonNull::JsonNull(std::istream& is)
{
  read_blanks_(is);
  if (is.get() != 'n'
      || is.get() != 'u'
      || is.get() != 'l'
      || is.get() != 'l')
    throw ParseError("invalid json null");
}

Json* JsonNull::clone() const
{
  return new JsonNull;
}

Json::Type JsonNull::type_get() const
{
  return Json::Type::NIL;
}

void JsonNull::write(std::ostream& os, int, int) const
{
  os << "null";
}
