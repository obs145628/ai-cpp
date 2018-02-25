#pragma once

#include <string>

namespace path
{

    static constexpr char SEP = '\\';

    std::string basename(const std::string& path);

}
