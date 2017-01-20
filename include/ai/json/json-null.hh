#pragma once

#include "json.hh"

class JsonNull : public Json
{
public:

  JsonNull() = default;
  JsonNull(std::istream& is);

  
  virtual Json* clone() const override;
  virtual Type type_get() const override;
  virtual void write(std::ostream& os,
                     int space, int level) const override;
};
