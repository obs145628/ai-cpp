#pragma once

#include <random>
#include "fwd.hh"

namespace nrandom
{

    class Random
    {
    public:

	static Random& instance();
	
	void seed(long s);
	long next_long();
	num_t next_double();

	num_t next_normal();

    private:
	std::mt19937 mt_;
	std::uniform_real_distribution<num_t> dist_double_;
	std::uniform_int_distribution<long> dist_long_;
	std::normal_distribution<num_t> dist_norm_;

	Random();
    };


    void seed(long s);

    template <class It>
    void shuffle(It begin, It end);

    template <class It>
    void fill_normal(It begin, It end);

    template <class It>
    void fill_long(It begin, It end);

    template <class It>
    void fill_long(It begin, It end, long max);

    template <class It>
    void fill_long(It begin, It end, long min, long max);

    template <class It>
    void fill_double(It begin, It end);

    template <class It>
    void fill_double(It begin, It end, double max);

    template <class It>
    void fill_double(It begin, It end, double min, double max);
}

#include "random.hxx"
