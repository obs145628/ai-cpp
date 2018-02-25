#pragma once

template <class T>
class Rect
{

public:

    Rect();
    Rect(const T& x, const T& y, const T& w, const T& h);
    Rect(const Rect&) = default;
    Rect(Rect&&) = default;
    ~Rect() = default;
    Rect& operator=(const Rect&) = default;
    Rect& operator=(Rect&&) = default;

    T left() const;
    T right() const;
    T top() const;
    T bottom() const;
    T center_x() const;
    T center_y() const;

    T x;
    T y;
    T w;
    T h;


};

#include "rect.hxx"
