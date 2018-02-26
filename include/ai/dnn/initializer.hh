#pragma once

#include "fwd.hh"
#include "../la/random.hh"

inline void gauss_initializer(num_t* begin, num_t* end)
{
    nrandom::fill_normal(begin, end);
}
