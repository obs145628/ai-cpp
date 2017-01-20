#include "io/dir.hh"
#include <cassert>
#include <cstdio>
#include <dirent.h>

std::vector<std::string> Dir::list_files(const std::string& path)
{
  DIR* d = opendir(path.c_str());
  assert(d);

  std::vector<std::string> res;

  struct dirent* dir;
  while ((dir = readdir(d)) != nullptr)
    {
      std::string name = dir->d_name;
      if (name != "." && name != "..")
        res.push_back(name);
    }

  closedir(d);

  return res;
}
