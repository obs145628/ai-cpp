#include "logic/model.hh"
#include <cassert>

namespace logic
{
  bool Model::var_get(const std::string& id) const
  {
    auto it = map_.find(id);
    assert(it != map_.end());
    return it->second;
  }
  
  bool Model::contains(const std::string& id) const
  {
    auto it = map_.find(id);
    return it != map_.end();
  }
  
  void Model::var_set(const std::string& id, bool value)
  {
    map_[id] = value;
  }
  
  void Model::clear()
  {
    map_.clear();
  }
}
