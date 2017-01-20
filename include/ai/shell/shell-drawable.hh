#pragma once

#include <vector>
#include "shell-canvas.hh"

class ShellDrawable
{
public:
  using vec_t = std::vector<ShellDrawable*>;
  
  ShellDrawable(const vec_t& children, int order);
  virtual ~ShellDrawable();

  virtual void move(int dx, int dy);
  virtual void draw(ShellCanvas& cvs, int dx, int dy) const = 0;

  const vec_t& children_get() const;
  int order_get() const;
  void order_set(int order);

  bool is_enabled() const;
  void enabled_set(bool enabled);
  bool is_visible() const;
  void visible_set(bool visible);

protected:
  vec_t children_;
  int order_;
  bool enabled_;
  bool visible_;
  
};
