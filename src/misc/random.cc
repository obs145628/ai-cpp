#include "misc/random.hh"
#include "shell/date.hh"

Random::Random()
        : Random(Date::now())
{}

Random::Random(long seed)
        : mt_(seed)
        , dist_double_(0.0, 1.0)
        , dist_long_()
{}


double Random::next_double()
{
    return dist_double_(mt_);
}

double Random::next_double(double max)
{
    return next_double() * max;
}

double Random::next_double(double min, double max)
{
    return next_double() * (max - min) + min;
}

double Random::next_gauss(double mean, double sd)
{
    static double next = 0.0;
    static bool has_next = false;

    if (!has_next)
    {
        double x;
        double y;
        double r;
        while (true)
        {
            x = 2.0 * next_double() - 1;
            y = 2.0 * next_double() - 1;
            r = x*x + y*y;
            if (r != 0 && r <= 1.0)
                break;
        }

        double d = std::sqrt(-2.0*std::log(r)/r);
        double n1 = x * d;
        next = y * d;
        has_next = true;
        return mean + n1 * sd;
    }

    else
    {
        has_next = false;
        return mean + next * sd;
    }
}

long Random::next_long()
{
    return dist_long_(mt_);
}

long Random::next_long(long max)
{
    return next_long() % max;
}

long Random::next_long(long min, long max)
{
    return next_long() % (max - min) + min;
}





void Random::fill_double(double* begin, double* end)
{
    for (auto it = begin; it != end; ++it)
        *it = next_double();
}

void Random::fill_double(double* begin, double* end, double max)
{
    for (auto it = begin; it != end; ++it)
        *it = next_double(max);
}

void Random::fill_double(double* begin, double* end, double min, double max)
{
    for (auto it = begin; it != end; ++it)
        *it = next_double(min, max);
}

void Random::fill_gauss(double* begin, double* end,
                        double mean, double sd)
{
    for (auto it = begin; it != end; ++it)
        *it = next_gauss(mean, sd);
}
