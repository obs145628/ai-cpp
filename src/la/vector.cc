#include "la/vector.hh"
#include <algorithm>
#include <cassert>
#include "la/functions.hh"
#include "io/serial.hh"

std::ostream &operator<<(std::ostream &os, const Vector &v)
{
    os << "{";
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        os << v[i];
        if (i + 1 != v.size())
            os << ", ";
    }
    os << "}";
    return os;
}

SerialWriter& operator<<(SerialWriter& os, const Vector& v)
{
    os << v.size();
    os.write(v.begin(), v.end());
    return os;
}

SerialReader& operator>>(SerialReader& is, Vector& v)
{
    std::size_t  size;
    is >> size;
    v.assign(size);
    is.read(v.begin(), v.end());

    return is;
}
