#pragma once

#include <string>
#include <iostream>

class JsonNull;
class JsonBool;
class JsonNumber;
class JsonString;
class JsonArray;
class JsonObject;

class Json
{
public:
  enum class Type
    {
      OBJECT,
      ARRAY,
      STRING,
      NUMBER,
      BOOL,
      NIL
    };
  
  virtual ~Json();

  virtual Json* clone() const = 0;
  virtual Type type_get() const = 0;
  virtual void write(std::ostream& os,
                     int space, int level) const = 0;

  std::string toString(int space = -1) const;
  bool is_object() const;
  bool is_array() const;
  bool is_string() const;
  bool is_number() const;
  bool is_bool() const;
  bool is_null() const;

  JsonNull& to_null();
  JsonBool& to_bool();
  JsonNumber& to_number();
  JsonString& to_string();
  JsonArray& to_array();
  JsonObject& to_object();
  const JsonNull& to_null() const;
  const JsonBool& to_bool() const;
  const JsonNumber& to_number() const;
  const JsonString& to_string() const;
  const JsonArray& to_array() const;
  const JsonObject& to_object() const;

  static Json* parse(std::istream& is);

protected:

  static void write_string_(std::ostream& os,
                            const std::string& str);
  static void write_spaces_(std::ostream& os,
                            int level);

  static void read_blanks_(std::istream& is);
  static std::string read_string_(std::istream& is);
};

std::ostream& operator<<(std::ostream& os, const Json& j);
