#pragma once

#include "json.hh"

class JsonString : public Json
{
public:
  JsonString(const std::string& value = {});
  JsonString(std::istream& is);
  
  virtual Json* clone() const override;
  virtual Type type_get() const override;
  virtual void write(std::ostream& os,
                     int space, int level) const override;

  const std::string& value_get() const;
  void value_set(const std::string& value);

private:
  std::string value_;
};
