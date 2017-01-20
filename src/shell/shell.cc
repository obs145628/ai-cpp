#include "shell/shell.hh"
#include <sys/ioctl.h>


const char* Shell::BOLD = "\x1b[1m";
const char* Shell::DIM = "\x1b[2m";
const char* Shell::UNDERLINED = "\x1b[4m";
const char* Shell::BLINK = "\x1b[5m";
const char* Shell::REVERSE = "\x1b[7m";
const char* Shell::HIDDEN = "\x1b[8m";
const char* Shell::RESET = "\x1b[0m";
const char* Shell::RESET_BOLD = "\x1b[21m";
const char* Shell::RESET_DIM = "\x1b[22m";
const char* Shell::RESET_UNDERLINED = "\x1b[24m";
const char* Shell::RESET_BLINK = "\x1b[25m";
const char* Shell::RESET_REVERSE = "\x1b[27m";
const char* Shell::RESET_HIDDEN = "\x1b[28m";
const char* Shell::FG_DEFAULT = "\x1b[39m";
const char* Shell::FG_BLACK = "\x1b[30m";
const char* Shell::FG_RED = "\x1b[31m";
const char* Shell::FG_GREEN = "\x1b[32m";
const char* Shell::FG_YELLOW = "\x1b[33m";
const char* Shell::FG_BLUE = "\x1b[34m";
const char* Shell::FG_MAGENTA = "\x1b[35m";
const char* Shell::FG_CYAN = "\x1b[36m";
const char* Shell::FG_LGRAY = "\x1b[37m";
const char* Shell::FG_DGRAY = "\x1b[90m";
const char* Shell::FG_LRED = "\x1b[91m";
const char* Shell::FG_LGREEN = "\x1b[92m";
const char* Shell::FG_LYELLOW = "\x1b[93m";
const char* Shell::FG_LBLUE = "\x1b[94m";
const char* Shell::FG_LMAGENTA = "\x1b[95m";
const char* Shell::FG_LCYAN = "\x1b[96m";
const char* Shell::FG_WHITE = "\x1b[97m";
const char* Shell::BG_DEFAULT = "\x1b[49m";
const char* Shell::BG_BLACK = "\x1b[40m";
const char* Shell::BG_RED = "\x1b[41m";
const char* Shell::BG_GREEN = "\x1b[42m";
const char* Shell::BG_YELLOW = "\x1b[43m";
const char* Shell::BG_BLUE = "\x1b[44m";
const char* Shell::BG_MAGENTA = "\x1b[45m";
const char* Shell::BG_CYAN = "\x1b[46m";
const char* Shell::BG_LGRAY = "\x1b[47m";
const char* Shell::BG_DGRAY = "\x1b[100m";
const char* Shell::BG_LRED = "\x1b[101m";
const char* Shell::BG_LGREEN = "\x1b[102m";
const char* Shell::BG_LYELLOW = "\x1b[103m";
const char* Shell::BG_LBLUE = "\x1b[104m";
const char* Shell::BG_LMAGENTA = "\x1b[105m";
const char* Shell::BG_LCYAN = "\x1b[106m";
const char* Shell::BG_WHITE = "\x1b[107m";

void Shell::clear()
{
  std::cout << "\033[2J\033[1;1H";
  std::cout.flush();
}

std::pair<int, int> Shell::size_get()
{
  std::pair<int, int> res;
  size_get(res.first, res.second);
  return res;
}

void Shell::size_get(int& width, int& height)
{
  struct winsize size;
  ioctl(1, TIOCGWINSZ, &size);
  width = size.ws_col;
  height = size.ws_row;
}

void Shell::move_cursor(int x, int y)
{
  std::cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}
