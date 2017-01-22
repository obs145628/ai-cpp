#include "json/json-object.hh"
#include "misc/parse-error.hh"

JsonObject::JsonObject(std::istream& is)
{
  read_blanks_(is);
  if (is.get() != '{')
    throw ParseError("invalid json object: expected '{'");

  read_blanks_(is);
  if (is.peek() == '}')
    {
      is.get();
      return;
    }

  while (true)
    {
      read_blanks_(is);
      std::string key = read_string_(is);
      read_blanks_(is);
      if (is.get() != ':')
        throw ParseError("invalid json object: expected ':'");

      map_[key] = Json::parse(is);
      read_blanks_(is);

      char c = is.get();
      if (c == '}')
        break;
      else if (c != ',')
        throw ParseError("invalid json object: expected ',' or '}'");
    }
}

JsonObject::~JsonObject()
{
  for (auto& it : map_)
    delete it.second;
}

Json* JsonObject::clone() const
{
  auto res = new JsonObject;
  for (const auto& it : map_)
    res->map_[it.first] = it.second->clone();
  return res;
}

Json::Type JsonObject::type_get() const
{
  return Json::Type::OBJECT;
}

void JsonObject::write(std::ostream& os,
                       int space, int level) const
{
  if (map_.empty())
    {
      os << "{}";
      return;
    }

  os << '{';
  if (space != -1)
    os << '\n';

  for (auto it = map_.begin(); it != map_.end(); ++it)
    {
      write_spaces_(os, level + space);
      write_string_(os, it->first);
      os << ": ";
      it->second->write(os, space, level + space);
      auto next = it;
      ++next;
      if (next != map_.end())
        os << ',';
      if (space != -1)
        os << '\n';
    }

  write_spaces_(os, level);
  os << '}';
}

bool JsonObject::empty() const
{
  return map_.empty();
}

std::size_t JsonObject::size() const
{
  return map_.size();
}

const Json& JsonObject::item_get(const std::string& key) const
{
  auto it = map_.find(key);
  if (it == map_.end())
    throw std::runtime_error{"JsonObject doen't have a field '"
        + key + "'"};
  return *(it->second);
}

bool JsonObject::contains(const std::string& key) const
{
  auto it = map_.find(key);
  return it != map_.end();
}

void JsonObject::erase(const std::string& key)
{
  auto it = map_.find(key);
  if (it == map_.end())
    throw std::runtime_error{"JsonObject doen't have a field '"
        + key + "'"};
  delete it->second;
  map_.erase(it);
}

void JsonObject::insert(const std::string& key, const Json& j)
{
  auto it = map_.find(key);
  if (it != map_.end())
    {
      delete it->second;
      it->second = j.clone();
    }
  else
    map_[key] = j.clone();
}
