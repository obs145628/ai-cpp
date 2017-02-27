#pragma once

#include <map>
#include <string>

namespace logic
{

  class Model
  {

  public:

    bool var_get(const std::string& id) const;
    bool contains(const std::string& id) const;
    void var_set(const std::string& id, bool value);
    void clear();

  private:
    std::map<std::string, bool> map_;
    
  };
  
}
