#include "json/json-string.hh"
#include "misc/parse-error.hh"

JsonString::JsonString(const std::string& value)
  : value_(value)
{}

JsonString::JsonString(std::istream& is)
{
  read_blanks_(is);
  value_ = read_string_(is);
}

Json* JsonString::clone() const
{
  return new JsonString(value_);
}

Json::Type JsonString::type_get() const
{
  return Json::Type::STRING;
}

void JsonString::write(std::ostream& os, int, int) const
{
  write_string_(os, value_);
}

const std::string& JsonString::value_get() const
{
  return value_;
}

void JsonString::value_set(const std::string& value)
{
  value_ = value;
}
