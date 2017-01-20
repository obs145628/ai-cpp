#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "shell.hh"

class ShellSprite
{
public:
  struct Pixel
  {
    char c;
    const char* fg;
    const char* bg;
    const char* sp;

    Pixel(char c = 0,
          const char* fg = Shell::FG_DEFAULT,
          const char* bg = Shell::BG_DEFAULT,
          const char* sp = "")
      : c(c)
      , fg(fg)
      , bg(bg)
      , sp(sp)
    {}
  };

  using data_t = std::vector<Pixel>;

  ShellSprite(std::size_t width, std::size_t height,
              const data_t& data);

  std::size_t width_get() const;
  std::size_t height_get() const;
  const data_t& data_get() const;

  const Pixel& at(std::size_t x, std::size_t y) const;

  static ShellSprite load(std::istream& is);
  static ShellSprite load(const std::string& path);
  

private:
  const std::size_t width_;
  const std::size_t height_;
  const data_t data_;

  static ShellSprite load_mono_(std::istream& is);
};
