#include "io/filesystem.hh"
#include <fstream>

namespace filesystem
{

    void copy_file(const std::string& src, const std::string& dst)
    {
        std::ifstream  is(src, std::ios::binary);
        std::ofstream  os(dst, std::ios::binary);
        os << is.rdbuf();
    }

}
