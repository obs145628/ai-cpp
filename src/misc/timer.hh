#pragma once

class Timer
{
public:
  Timer();

  long get() const;
  long reset();

private:
  long start_;
};

#include "timer.hxx"
