#pragma once

#include <cstdint>

class XorShift64
{

public:

    XorShift64();
    XorShift64(uint64_t seed);

    uint64_t next_u64();
    int next_int(int max);
    int next_int(int min, int max);
    long next_long(long max);
    long next_long(long min, long max);

    double next_double();
    double next_double(double max);
    double next_double(double min, double max);

private:
    uint64_t state_;


};

#include "xor-shift.hxx"
