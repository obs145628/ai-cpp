#pragma once

#include <string>
#include <vector>

class Arguments
{

public:

  Arguments(const std::vector<std::string>& args);
  Arguments(int argc, char** argv);

  const std::vector<std::string>& args_get() const;

  bool has_option(char s) const;
  bool has_option(const std::string& l) const;
  bool has_option(char s, const std::string& l) const;

private:
  std::vector<std::string> args_;
  
};
