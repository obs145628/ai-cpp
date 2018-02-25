#pragma once

#include <cstdint>

namespace bim {

    class Color
    {

    public:

        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
        static const Color BLACK;
        static const Color WHITE;

        static int clamp8(int x);
        static double clampf(double x);

        static Color from_rgb(uint32_t val);
        static Color from_rgb_f(double r, double g, double b);

        Color(int r, int g, int b, int a = 255);

        int rgb() const;

        int r() const;
        int g() const;
        int b() const;
        int a() const;

    private:
        int r_;
        int g_;
        int b_;
        int a_;
    };



}

#include "color.hxx"
