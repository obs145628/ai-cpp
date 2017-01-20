#include "shell/shell-scene.hh"
#include <unistd.h>
#include "shell/date.hh"

ShellScene::ShellScene(ShellCanvas& canvas)
  : canvas_(canvas)
  , sleep_(10)
  , running_(false)
{}

int ShellScene::start()
{
  long time = Date::now();

  on_start_();

  running_ = true;
  while (running_)
    {
      long bef = Date::now();
      delta_ = bef - time;
      time = bef;
      on_update_();
      render_();
      long rd_time = Date::now() - bef;
      if (rd_time < sleep_)
        usleep((sleep_ - rd_time) * 1e3);
    }

  return on_quit_();
}

void ShellScene::stop()
{
  running_ = false;
}

long ShellScene::sleep_get() const
{
  return sleep_;
}

void ShellScene::sleep_set(long sleep)
{
  sleep_ = sleep;
}

void ShellScene::on_start_()
{}

void ShellScene::on_update_()
{}

int ShellScene::on_quit_()
{
  return 0;
}

void ShellScene::render_()
{
  //canvas_.clear();
  //canvas_.render();
}
