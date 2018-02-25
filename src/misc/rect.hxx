#pragma once

#include "rect.hxx"

Rect::Rect()
        : Rect(0, 0, 0, 0)
{}

Rect::Rect(const T& x, const T& y, const T& w, const T& h)
        : x(x)
        , y(y)
        , w(w)
        , h(h)
{}

T Rect::left() const
{
    return x;
}

T Rect::right() const
{
    return x + w;
}

T Rect::top() const
{
    return y;
}

T Rect::bottom() const
{
    return y + h;
}

T Rect::center_x() const
{
    return x + w / T(2);
}

T Rect::center_y() const
{
    return y + h / T(2);
}
