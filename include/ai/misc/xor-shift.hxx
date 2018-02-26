#pragma once

#include "xor-shift.hh"
#include "../shell/date.hh"

inline XorShift64::XorShift64()
        : XorShift64(Date::now())
{}

inline XorShift64::XorShift64(uint64_t seed)
        : state_(seed)
{}

inline uint64_t XorShift64::next_u64()
{
    state_ ^= state_ >> 12;
    state_ ^= state_ << 25;
    state_ ^= state_ >> 27;
    return state_ * 0x2545F4914F6CDD1D;
}

inline int XorShift64::next_int(int max)
{
    uint64_t lim = max;
    return static_cast<int> (next_u64() % lim);
}

inline int XorShift64::next_int(int min, int max)
{
    uint64_t lim = max - min;
    return static_cast<int> (next_u64() % lim) + min;
}

inline long XorShift64::next_long(long max)
{
    uint64_t lim = max;
    return static_cast<long> (next_u64() % lim);
}

inline long XorShift64::next_long(long min, long max)
{
    uint64_t lim = max - min;
    return static_cast<long> (next_u64() % lim) + min;
}

inline double XorShift64::next_double()
{
    return next_u64() / static_cast<double> (UINT64_MAX);
}

inline double XorShift64::next_double(double max)
{
    return next_double() * max;
}

inline double XorShift64::next_double(double min, double max)
{
    return next_double() * (max - min) + min;
}
