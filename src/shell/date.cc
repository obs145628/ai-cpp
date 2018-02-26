#include "shell/date.hh"
#include <chrono>
#include <thread>

long Date::now()
{
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  using std::chrono::system_clock;
  return duration_cast<milliseconds>(
    system_clock::now()
    .time_since_epoch()).count();
}

void Date::sleep(long ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
