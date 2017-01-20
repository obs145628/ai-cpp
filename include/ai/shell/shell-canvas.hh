#pragma once

#include <string>
#include "shell.hh"
#include "shell-sprite.hh"

class ShellCanvas
{
public:

  struct Style
  {
    const char* fg;
    const char* bg;
    const char* sp;

    Style(const char* fg = Shell::FG_DEFAULT,
          const char* bg = Shell::BG_DEFAULT,
          const char* sp = "")
      : fg(fg)
      , bg(bg)
      , sp(sp)
    {}
  };
  
  ShellCanvas();
  ~ShellCanvas();

  void clear();
  void render();

  const Style& style_get() const;
  void style_set(const Style& style);
  int width_get() const;
  int height_get() const;

  void draw_char(int x, int y, char c);
  void draw_string(int x, int y, const std::string& str);
  void draw_cstr(int x, int y, const char* str, std::size_t len);

  void draw_sprite(int x, int y, const ShellSprite& sprite);
  void draw_sprite(int x, int y, const ShellSprite& sprite,
                   std::size_t clip_x, std::size_t clip_y,
                   std::size_t clip_w, std::size_t clip_h);

private:
  Style style_;
  int x_;
  int y_;
  int w_;
  int h_;
};
