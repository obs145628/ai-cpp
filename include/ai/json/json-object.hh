#pragma once

#include "json.hh"
#include <map>

class JsonObject : public Json
{
public:

  JsonObject() = default;
  JsonObject(std::istream& is);
  
  virtual ~JsonObject();
  virtual Json* clone() const override;
  virtual Type type_get() const override;
  virtual void write(std::ostream& os,
                     int space, int level) const override;

  bool empty() const;
  std::size_t size() const;
  const Json& item_get(const std::string& key) const;
  bool contains(const std::string& key) const;
  void erase(const std::string& key);
  void insert(const std::string& key, const Json& j);

private:
  std::map<std::string, Json*> map_;
};
