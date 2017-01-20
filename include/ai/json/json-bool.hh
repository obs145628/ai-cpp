#pragma once

#include "json.hh"

class JsonBool : public Json
{
public:
  JsonBool(bool value = false);
  JsonBool(std::istream& is);
  
  virtual Json* clone() const override;
  virtual Type type_get() const override;
  virtual void write(std::ostream& os,
                     int space, int level) const override;

  bool value_get() const;
  void value_set(bool value);

private:
  bool value_;
};
