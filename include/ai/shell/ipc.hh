#pragma once

#include <string>

class IPC
{
public:

  IPC(const std::string& cmd);
  ~IPC();

  bool connect();
  bool write(const std::string& message);
  bool read_line(std::string& out);
  std::string read_line();


private:
  std::string cmd_;
  int fd_in_;
  int fd_out_;
};
