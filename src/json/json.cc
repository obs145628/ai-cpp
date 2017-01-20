#include "json/json.hh"
#include <sstream>
#include "json/json-null.hh"
#include "json/json-bool.hh"
#include "json/json-number.hh"
#include "json/json-string.hh"
#include "json/json-array.hh"
#include "json/json-object.hh"
#include "misc/parse-error.hh"

Json::~Json()
{}

std::string Json::toString(int space) const
{
  std::ostringstream os;
  write(os, space, 0);
  return os.str();
}

bool Json::is_object() const
{
  return type_get() == Type::OBJECT;
}

bool Json::is_array() const
{
  return type_get() == Type::ARRAY;
}

bool Json::is_string() const
{
  return type_get() == Type::STRING;
}

bool Json::is_number() const
{
  return type_get() == Type::NUMBER;
}

bool Json::is_bool() const
{
  return type_get() == Type::BOOL;
}

bool Json::is_null() const
{
  return type_get() == Type::NIL;
}

Json* Json::parse(std::istream& is)
{
  read_blanks_(is);
  char c = is.peek();
  if (c == 'n')
    return new JsonNull(is);
  else if (c == 't' || c == 'f')
    return new JsonBool(is);
  else if (c == '-' || (c >= '0' && c <= '9'))
    return new JsonNumber(is);
  else if (c == '"')
    return new JsonString(is);
  else if (c == '[')
    return new JsonArray(is);
  else if (c == '{')
    return new JsonObject(is);
  else
    throw ParseError("invalid json value");
}

void Json::write_string_(std::ostream& os,
                         const std::string& str)
{
  os << '"';
  for (char c: str)
    {
      if (c == '\\' || c == '"')
        os << '\\' << c;
      else if (c == '\n')
        os << "\\n";
      else if (c == '\t')
        os << "\\t";
      else
      os << c;
    }
  os << '"';
}

void Json::write_spaces_(std::ostream& os,
                         int level)
{
  for (int i = 0; i < level; ++i)
    os << ' ';
}

void Json::read_blanks_(std::istream& is)
{
  while (true)
    {
      char c = is.peek();
      if (c != ' ' && c != '\t' && c != '\n')
        break;
      is.get();
    }
}

std::string Json::read_string_(std::istream& is)
{
  std::ostringstream ss;

  if(is.get() != '"')
    throw ParseError("invalid json string");

  bool escaped = false;
  while (true)
    {
      if (!is.good())
        throw ParseError("invalid json string");
      char c = is.get();

      if (escaped)
        {
          if (c == '\\' || c == '"')
            ss << c;
          else if (c == 'n')
            ss << '\n';
          else if (c == 't')
            ss << '\t';
          else
            throw ParseError("Invalid json string");
          escaped = false;
        }

      else
        {
          if (c == '"')
            break;
          else if (c == '\\')
            escaped = true;
          else
            ss << c;
        }
    }

  return ss.str();
}


std::ostream& operator<<(std::ostream& os, const Json& j)
{
  j.write(os, -1, 0);
  return os;
}
