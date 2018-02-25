#include "graphics/color.hh"
#include <algorithm>

uint8_t Color::clampi(int x)
{
    int val = std::max(0, std::min(x, 255));
    return static_cast<uint8_t>(val);
}

double Color::clampf(double x)
{
    return std::max(0., std::min(x, 1.));
}

Color::Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
        : r_(r)
        , g_(g)
        , b_(b)
        , a_(a)
{}

uint8_t Color::r() const
{
    return r_;
}
uint8_t Color::g() const
{
    return g_;
}

uint8_t Color::b() const
{
    return b_;
}

uint8_t Color::a() const
{
    return a_;
}

void Color::r_set(int r)
{
    r_ = clampi(r);
}

void Color::g_set(int g)
{
    g_ = clampi(g);
}

void Color::b_set(int b)
{
    b_ = clampi(b);
}

void Color::a_set(int a)
{
    a_ = clampi(a);
}

double Color::dr() const
{
    return r_ / 255.;
}

double Color::dg() const
{
    return g_ / 255;
}

double Color::db() const
{
    return b_ / 255;
}

double Color::da() const
{
    return a_ / 255;
}

void Color::dr_set(double r)
{
    r_ = static_cast<uint8_t >(clampf(r) * 255.);
}

void Color::dg_set(double g)
{
    g_ = static_cast<uint8_t >(clampf(g) * 255.);
}

void Color::db_set(double b)
{
    b_ = static_cast<uint8_t >(clampf(b) * 255.);
}

void Color::da_set(double a)
{
    a_ = static_cast<uint8_t >(clampf(a) * 255.);
}

uint32_t Color::to_rgba() const
{
    return (r_ << 24)
           | (g_ << 16)
           | (b_ << 8)
           | (a_ << 0);
}

uint32_t Color::to_argb() const {
    return (a_ << 24)
           | (r_ << 16)
           | (g_ << 8)
           | (b_ << 0);
}

const Color Color::RED {255, 0, 0};
const Color Color::GREEN {0, 255, 0};
const Color Color::BLUE {0, 0, 255};
const Color Color::YELLOW {255, 255, 0};
const Color Color::MAGENTA {255, 0, 255};
const Color Color::CYAN {0, 255, 255};
const Color Color::WHITE {255, 255, 255};
const Color Color::BLACK {0, 0, 0};
