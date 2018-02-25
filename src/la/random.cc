#include "la/random.hh"
#include "shell/date.hh"

namespace nrandom
{

    Random& Random::instance()
    {
	static Random res;
	return res;
    }
    
    void Random::seed(long s)
    {
	mt_ = std::mt19937(s);
    }
    
    long Random::next_long()
    {
	return dist_long_(mt_);
    }
    
    num_t Random::next_double()
    {
	return dist_double_(mt_);
    }

    num_t Random::next_normal()
    {
	return dist_norm_(mt_);
    }


    Random::Random()
	: mt_(Date::now())
        , dist_double_(0.0, 1.0)
        , dist_long_()
	, dist_norm_(0.0, 1.0)
    {}





    void seed(long s)
    {
	Random::instance().seed(s);
    }

}
