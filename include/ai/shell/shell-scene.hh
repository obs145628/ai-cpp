#pragma once

#include <vector>
#include "shell-canvas.hh"
#include "shell-drawable.hh"

class ShellScene
{
public:
  ShellScene(ShellCanvas& canvas);

  int start();
  void stop();

  long sleep_get() const;
  void sleep_set(long sleep);

protected:
  ShellCanvas& canvas_;
  long delta_;

  virtual void on_start_();
  virtual void on_update_();
  virtual int on_quit_();
  

private:
  long sleep_;
  bool running_;

  void render_();

  class DrawCmp
  {
    bool operator()(const ShellDrawable* left,
                    const ShellDrawable* right) const
    {
      return left->order_get() < right->order_get();
    }
  };
};
