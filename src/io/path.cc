#include "io/path.hh"

namespace path
{

    std::string basename(const std::string& path)
    {
        std::size_t pos = path.find_last_of(SEP);
        if (pos == std::string::npos)
            return path;
        else
            return path.substr(pos + 1);
    }

}

