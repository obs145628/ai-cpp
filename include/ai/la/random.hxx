#pragma once

#include "random.hh"


namespace nrandom
{


    template <class It>
    void shuffle(It begin, It end)
    {
	if (begin == end)
	    return;

	std::size_t n = end - begin;

	for (std::size_t i = n - 1; i < n; --i)
	{
	    std::size_t j = Random::instance().next_long() % (i + 1);
	    std::swap(*(begin + i), *(begin + j));
	}
    }

    template <class It>
    void fill_normal(It begin, It end)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_normal();
    }


    template <class It>
    void fill_long(It begin, It end)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_long();
    }

    template <class It>
    void fill_long(It begin, It end, long max)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_long() % max;
    }

    template <class It>
    void fill_long(It begin, It end, long min, long max)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_long() % (max - min) + min;
    }

    template <class It>
    void fill_double(It begin, It end)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_double();
    }

    template <class It>
    void fill_double(It begin, It end, double max)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_double() * max;
    }

    template <class It>
    void fill_double(It begin, It end, double min, double max)
    {
	while (begin != end)
	    *(begin++) = Random::instance().next_double() * (max - min) + min;
    }
}
