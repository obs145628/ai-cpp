#include "shell/arguments.hh"
#include <algorithm>

Arguments::Arguments(const std::vector<std::string>& args)
  : args_(args)
{}

Arguments::Arguments(int argc, char** argv)
{
  for (int i = 0; i < argc; ++i)
    args_.push_back(argv[i]);
}

const std::vector<std::string>& Arguments::args_get() const
{
  return args_;
}

bool Arguments::has_option(char s) const
{
  std::string query = "--";
  query[1] = s;
  return std::find(args_.begin(), args_.end(), query) != args_.end();
}

bool Arguments::has_option(const std::string& l) const
{
  std::string query = "--" + l;
  return std::find(args_.begin(), args_.end(), query) != args_.end();
}

bool Arguments::has_option(char s, const std::string& l) const
{
  return has_option(s) || has_option(l);
}
