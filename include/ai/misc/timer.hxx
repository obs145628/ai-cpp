#include "timer.hh"
#include "../shell/date.hh"

Timer::Timer()
  : start_(Date::now())
{}

long Timer::get() const
{
  return Date::now() - start_;
}

long Timer::reset()
{
  long now = Date::now();
  long res = now - start_;
  start_ = now;
  return res;
}
