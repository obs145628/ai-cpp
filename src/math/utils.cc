#include "math/utils.hh"
#include <cmath>

#define REAL_DELTA (1e-5)

bool is_null(real_t x)
{
  return x == 0;
}

bool is_fnull(real_t x)
{
  return std::abs(x) < REAL_DELTA;
}

bool fequals(real_t l, real_t r)
{
  return std::abs(l - r) < REAL_DELTA;
}
