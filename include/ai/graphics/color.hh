#pragma once

#include <cstdint>

class Color
{

public:

    static uint8_t clampi(int x);
    static double clampf(double x);

    Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);
    Color(const Color&) = default;
    Color(Color&&) = default;
    ~Color() = default;

    Color& operator=(const Color&) = default;
    Color& operator=(Color&&) = default;

    uint8_t r() const;
    uint8_t g() const;
    uint8_t b() const;
    uint8_t a() const;
    void r_set(int r);
    void g_set(int g);
    void b_set(int b);
    void a_set(int a);

    double dr() const;
    double dg() const;
    double db() const;
    double da() const;

    void dr_set(double r);
    void dg_set(double g);
    void db_set(double b);
    void da_set(double a);

    uint32_t to_rgba() const;
    uint32_t to_argb() const;

    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color MAGENTA;
    static const Color CYAN;
    static const Color WHITE;
    static const Color BLACK;

private:

    std::uint8_t r_;
    std::uint8_t g_;
    std::uint8_t b_;
    std::uint8_t  a_;
};
