#include "math/random.hh"
#include "shell/date.hh"

Random::Random()
  : Random(Date::now())
{}

Random::Random(unsigned long s)
  : mt_()
  , mti_(1)
  , mag01_ {0x0UL, MATRIX_A}
{
  mt_[0] = s & 0xffffffffUL;
  for (; mti_ < N; ++mti_)
		{
			mt_[mti_] = (1812433253UL * (mt_[mti_ - 1]
                                   ^ (mt_[mti_ - 1] >> 30)) + mti_);
			mt_[mti_] &= 0xffffffffUL;
		}
}

unsigned long
Random::int32_get()
{
  unsigned long y;

  if (mti_ == N)
		{
			int kk;

			for (kk = 0; kk < N - M; ++kk)
        {
          y = (mt_[kk] & UPPER_MASK)
            | (mt_[kk + 1] & LOWER_MASK);
          mt_[kk] = mt_[kk + M] ^ (y >> 1) ^ mag01_[y & 0x1UL];
        }
			for (; kk < N - 1; ++kk)
        {
          y = (mt_[kk ] & UPPER_MASK)
            | (mt_[kk + 1 ] & LOWER_MASK);
          mt_[kk] = mt_[kk + ( M - N)] ^ (y >> 1)
            ^ mag01_ [y & 0x1UL];
        }
			y = (mt_[N - 1] & UPPER_MASK)
				| (mt_[0 ] & LOWER_MASK);
			mt_[N - 1] = mt_ [M - 1] ^ (y >> 1)
				^ mag01_[y & 0x1UL];

			mti_ = 0;
		}

  y = mt_[mti_++];
  y ^= (y >> 11);
  y ^= (y << 7) & 0x9d2c5680UL;
  y ^= (y << 15) & 0xefc60000UL;
  y ^= (y >> 18);
  return y;
}


long
Random::int31_get()
{
  long val = int32_get();
  return val >> 1;
}


bool
Random::bool_get()
{
  return int32_get() % 2;
}

float
Random::float_get()
{
  float inv = 1.0f / 4294967295.0f;
  return int32_get() * inv;
}


double
Random::double_get()
{
  double inv = 1.0 / 4294967295.0;
  return int32_get() * inv;
}


float
Random::float_get(float max)
{
  return float_get() * max;
}

double
Random::double_get(double max)
{
  return double_get() * max;
}


float
Random::float_get(float min, float max)
{
  return float_get() * (max - min) + min;
}

double
Random::double_get(double min, double max)
{
  return double_get() * (max - min) + min;
}
