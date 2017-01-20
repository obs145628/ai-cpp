#pragma once
#include <string>


class Command
{
public:
  static int exec(const std::string& cmd);
  static std::string sub(const std::string& cmd);
  static int sub2(const std::string& cmd, std::string& out,
                  std::string& err);

private:
  static std::string read_fd_(int fd);
};
