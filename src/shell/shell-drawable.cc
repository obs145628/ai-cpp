#include "shell/shell-drawable.hh"

ShellDrawable::ShellDrawable(const vec_t& children, int order)
  : children_(children)
  , order_(order)
{}

ShellDrawable::~ShellDrawable()
{}

void ShellDrawable::move(int dx, int dy)
{
  for (auto child: children_)
    child->move(dx, dy);
}

const ShellDrawable::vec_t&
ShellDrawable::children_get() const
{
  return children_;
}

int ShellDrawable::order_get() const
{
  return order_;
}

void ShellDrawable::order_set(int order)
{
  order_ = order;
}

bool ShellDrawable::is_enabled() const
{
  return enabled_;
}

void ShellDrawable::enabled_set(bool enabled)
{
  enabled_ = enabled;
}

bool ShellDrawable::is_visible() const
{
  return visible_;
}

void ShellDrawable::visible_set(bool visible)
{
  visible_ = visible;
}

