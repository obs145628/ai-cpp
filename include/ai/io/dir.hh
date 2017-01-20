#pragma once

#include <string>
#include <vector>

class Dir
{
public:
  static std::vector<std::string> list_files(const std::string& path);
};
