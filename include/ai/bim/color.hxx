#pragma once

#include "color.hh"
#include <algorithm>

namespace bim
{

    inline double Color::clampf(double x)
    {
        return std::max(0., std::min(x, 1.));
    }

    inline int Color::clamp8(int x)
    {
        return std::max(0, std::min(x, 255));
    }

    inline Color Color::from_rgb(uint32_t val)
    {
        return Color(
                (val >> 0) & 0xFF,
                (val >> 8) & 0xFF,
                (val >> 16) & 0xFF
        );
    }

    inline Color Color::from_rgb_f(double r, double g, double b)
    {
        return Color(
                clampf(r) / 255.,
                clampf(g) / 255.,
                clampf(b) / 255.
        );
    }

    inline Color::Color(int r, int g, int b, int a)
            : r_(clamp8(r))
            , g_(clamp8(g))
            , b_(clamp8(b))
            , a_(clamp8(a))
    {}


    inline int Color::rgb() const
    {
        return (r_ << 0) | (g_ << 8) | (b_ << 16);
    }

    inline int Color::r() const
    {
        return r_;
    }

    inline int Color::g() const
    {
        return g_;
    }

    inline int Color::b() const
    {
        return b_;
    }

    inline int Color::a() const
    {
        return a_;
    }

}
