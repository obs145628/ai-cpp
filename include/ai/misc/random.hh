#pragma once

#include <random>


class Random
{
public:

    Random();
    Random(long seed);

    double next_double();
    double next_double(double max);
    double next_double(double min, double max);

    double next_gauss(double mean = 0.0, double sd = 1.0);

    long next_long();
    long next_long(long max);
    long next_long(long min, long max);

    void fill_double(double* begin, double* end);
    void fill_double(double* begin, double* end, double max);
    void fill_double(double* begin, double* end, double min, double max);

    void fill_gauss(double* begin, double* end,
                    double mean = 0.0, double sd = 1.0);


    template <class It>
    void shuffle(It begin, It end);

private:
    std::mt19937 mt_;
    std::uniform_real_distribution<double> dist_double_;
    std::uniform_int_distribution<long> dist_long_;
};

#include "random.hxx"
