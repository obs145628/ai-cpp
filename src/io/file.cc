#include "io/file.hh"
#include <fstream>

void File::writeText(const std::string &path, const std::string& content)
{
  std::ofstream os(path, std::ios::binary);
  os << content;
}
