#include "shell/shell-canvas.hh"
#include <iostream>
#include "shell/shell.hh"

ShellCanvas& ShellCanvas::instance()
{
    static ShellCanvas cvs;
    return cvs;
}

ShellCanvas::ShellCanvas()
{
  clear();
  std::cout << style_.fg
            << style_.bg
            << style_.sp;
}

ShellCanvas::~ShellCanvas()
{
  std::cout << Shell::FG_DEFAULT
            << Shell::BG_DEFAULT
            << std::endl;
}

void ShellCanvas::clear()
{
  Shell::clear();
  x_ = 0;
  y_ = 0;
  Shell::size_get(w_, h_);
}

void ShellCanvas::render()
{
  std::cout.flush();
}

const ShellCanvas::Style&
ShellCanvas::style_get() const
{
  return style_;
}

void ShellCanvas::style_set(const Style& style)
{
  if (style.fg != style_.fg)
    std::cout << style.fg;
  if (style.bg != style_.bg)
    std::cout << style.bg;
  if (style.sp != style_.sp)
    std::cout << style.sp;
  style_ = style;
}

int ShellCanvas::width_get() const
{
  return w_;
}

int ShellCanvas::height_get() const
{
  return h_;
}

void ShellCanvas::draw_char(int x, int y, char c)
{
  if (x < 0 || x >= w_ || y < 0 || y >= h_)
    return;

  if (x != x_ || y != y_)
    Shell::move_cursor(x, y);

  std::cout << c;

  x_ = x + 1 < w_ ? x + 1 : 0;
  y_ = y + !!x_;
}

void ShellCanvas::draw_string(int x, int y, const std::string& str)
{
  draw_cstr(x, y, str.c_str(), str.size());
}

void ShellCanvas::draw_cstr(int x, int y, const char* str, std::size_t len)
{
  for (std::size_t i = 0; i < len; ++i)
    draw_char(x + i, y, str[i]);
}

void ShellCanvas::draw_sprite(int x, int y, const ShellSprite& sprite)
{
  draw_sprite(x, y, sprite, 0, 0,
              sprite.width_get(), sprite.height_get());
}

void ShellCanvas::draw_sprite(int x, int y, const ShellSprite& sprite,
                              std::size_t clip_x, std::size_t clip_y,
                              std::size_t clip_w, std::size_t clip_h)
{
  auto style = style_get();

  for (std::size_t i = 0; i < clip_h; ++i)
    for (std::size_t j = 0; j < clip_w; ++j)
      {
        const auto& px = sprite.at(clip_x + j, clip_y + i);
        if (!px.c)
          continue;
        style_set(Style{px.fg, px.bg, px.sp});
        draw_char(x + j, y + i, px.c);
      }

  style_set(style);
}
