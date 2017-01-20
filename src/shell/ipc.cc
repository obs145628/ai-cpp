#include "shell/ipc.hh"
#include <cassert>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

IPC::IPC(const std::string& cmd)
  : cmd_(cmd)
  , fd_in_(-1)
  , fd_out_(-1)
{}

IPC::~IPC()
{
  close(fd_in_);
  close(fd_out_);
}

bool IPC::connect()
{
  int fds_in[2];
  int fds_out[2];
  if (pipe(fds_in) == -1 || pipe(fds_out) == -1)
    return false;

  fd_in_ = fds_in[0];
  fd_out_ = fds_out[1];

  pid_t pid = fork();
  if (pid == -1)
    return false;

  char str[2048];
  strcpy(str, cmd_.c_str());

  char* const args[] =
    {
      str,
      nullptr
    };

  if (!pid) //children
    {
      dup2(fds_out[0], STDIN_FILENO);
      dup2(fds_in[1], STDOUT_FILENO);
      close(fds_out[0]);
      close(fds_in[1]);
      close(fds_out[1]);
      close(fds_in[0]);
      execvp(args[0], args);
    }

  else
    {
      close(fds_in[1]);
      close(fds_out[0]);
    }


  return true;
}

bool IPC::write(const std::string& message)
{
  std::size_t res = ::write(fd_out_, message.c_str(), message.size());
  return res == message.size();
}

bool IPC::read_line(std::string& out)
{
  std::string buf;

  while(true)
    {
      char c;
      auto nb = ::read(fd_in_, &c, 1);
      if (nb <= 0 && buf.empty())
        return false;
      if (!nb || c == '\n')
        break;
      buf.push_back(c);
    }

  out = buf;
  return true;
}

std::string IPC::read_line()
{
  std::string res;
  read_line(res);
  return res;
}
