#pragma once

#include <iostream>
#include <utility>


class Shell
{

public:

  static const char* BOLD;
  static const char* DIM;
  static const char* UNDERLINED;
  static const char* BLINK;
  static const char* REVERSE;
  static const char* HIDDEN;
  static const char* RESET;
  static const char* RESET_BOLD;
  static const char* RESET_DIM;
  static const char* RESET_UNDERLINED;
  static const char* RESET_BLINK;
  static const char* RESET_REVERSE;
  static const char* RESET_HIDDEN;
  static const char* FG_DEFAULT;
  static const char* FG_BLACK;
  static const char* FG_RED;
  static const char* FG_GREEN;
  static const char* FG_YELLOW;
  static const char* FG_BLUE;
  static const char* FG_MAGENTA;
  static const char* FG_CYAN;
  static const char* FG_LGRAY;
  static const char* FG_DGRAY;
  static const char* FG_LRED;
  static const char* FG_LGREEN;
  static const char* FG_LYELLOW;
  static const char* FG_LBLUE;
  static const char* FG_LMAGENTA;
  static const char* FG_LCYAN;
  static const char* FG_WHITE;
  static const char* BG_DEFAULT;
  static const char* BG_BLACK;
  static const char* BG_RED;
  static const char* BG_GREEN;
  static const char* BG_YELLOW;
  static const char* BG_BLUE;
  static const char* BG_MAGENTA;
  static const char* BG_CYAN;
  static const char* BG_LGRAY;
  static const char* BG_DGRAY;
  static const char* BG_LRED;
  static const char* BG_LGREEN;
  static const char* BG_LYELLOW;
  static const char* BG_LBLUE;
  static const char* BG_LMAGENTA;
  static const char* BG_LCYAN;
  static const char* BG_WHITE;

  static void clear();

  static std::pair<int, int> size_get();
  static void size_get(int& width, int& height);

  static void move_cursor(int x, int y);
  
};
