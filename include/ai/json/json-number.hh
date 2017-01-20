#pragma once

#include "json.hh"

class JsonNumber : public Json
{
public:
  JsonNumber(long n = 0);
  JsonNumber(double n);
  JsonNumber(std::istream& is);

  virtual Json* clone() const override;
  virtual Type type_get() const override;
  virtual void write(std::ostream& os,
                     int space, int level) const override;

  bool is_int() const;
  long int_get() const;
  double double_get() const;
  void int_set(long n);
  void double_set(double n);

private:
  bool is_int_;
  long ival_;
  double dval_;
};
