#pragma once

#include "json.hh"
#include <vector>

class JsonArray : public Json
{
public:

  JsonArray() = default;
  JsonArray(std::istream& is);
  ~JsonArray();
  virtual Json* clone() const override;
  virtual Type type_get() const override;
  virtual void write(std::ostream& os,
                     int space, int level) const override;

  bool empty() const;
  std::size_t size() const;
  const Json& item_get(std::size_t pos) const;
  void item_set(std::size_t pos, const Json& j);
  void insert(std::size_t pos, const Json& j);
  void erase(std::size_t pos);

  void push_front(const Json& j);
  void push_back(const Json& j);
  void pop_front();
  void pop_back();

private:
  std::vector<Json*> arr_;
};
