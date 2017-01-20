#include "json/json-array.hh"
#include "misc/parse-error.hh"
#include <cassert>

JsonArray::JsonArray(std::istream& is)
{
  read_blanks_(is);
  if (is.get() != '[')
    throw ParseError("invalid json array");

  read_blanks_(is);
  if (is.peek() == ']')
    {
      is.get();
      return;
    }

  while (true)
    {
      arr_.push_back(Json::parse(is));
      read_blanks_(is);

      char c = is.get();
      if (c == ']')
        break;
      else if (c != ',')
        throw ParseError("invalid json array");
    }
}

JsonArray::~JsonArray()
{
  for (auto val : arr_)
    delete val;
}

Json* JsonArray::clone() const
{
  auto res = new JsonArray;
  for(const auto val : arr_)
    res->arr_.push_back(val->clone());
  return res;
}

Json::Type JsonArray::type_get() const
{
  return Json::Type::ARRAY;
}

void JsonArray::write(std::ostream& os,
                      int space, int level) const
{
  if (arr_.empty())
    {
      os << "[]";
      return;
    }

  os << '[';
  if (space != -1)
    os << '\n';

  for (std::size_t i = 0; i < arr_.size(); ++i)
    {
      write_spaces_(os, level + space);
      arr_[i]->write(os, space, level + space);
      if (i + 1 < arr_.size())
        os << ',';
      if (space != -1)
        os << '\n';
    }

  write_spaces_(os, level);
  os << ']';
}

bool JsonArray::empty() const
{
  return arr_.empty();
}

std::size_t JsonArray::size() const
{
  return arr_.size();
}

const Json& JsonArray::item_get(std::size_t pos) const
{
  assert(pos < arr_.size());
  return *(arr_[pos]);
}

void JsonArray::item_set(std::size_t pos, const Json& j)
{
  assert(pos < arr_.size());
  delete arr_[pos];
  arr_[pos] = j.clone();
}

void JsonArray::insert(std::size_t pos, const Json& j)
{
  assert(pos <= arr_.size());
  arr_.insert(arr_.begin() + pos, j.clone()); 
}
void JsonArray::erase(std::size_t pos)
{
  assert(pos < arr_.size());
  delete arr_[pos];
  arr_.erase(arr_.begin() + pos);
}

void JsonArray::push_front(const Json& j)
{
  insert(0, j);
}

void JsonArray::push_back(const Json& j)
{
  insert(arr_.size(), j);
}

void JsonArray::pop_front()
{
  erase(0);
}

void JsonArray::pop_back()
{
  erase(arr_.size() - 1);
}
