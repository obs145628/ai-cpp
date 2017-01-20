#include "shell/command.hh"
#include <cstdlib>
#include <unistd.h>

int Command::exec(const std::string& cmd)
{
  return std::system(cmd.c_str());
}

std::string Command::sub(const std::string& cmd)
{
  int fds[2];
  pipe(fds);
  int out_copy = dup(1);
  dup2(fds[1], 1);
  std::system(cmd.c_str());

  close(fds[1]);
  dup2(out_copy, 1);
  std::string res = read_fd_(fds[0]);
  close(fds[0]);
  close(out_copy);
  return res;
}

int Command::sub2(const std::string& cmd, std::string& out,
                  std::string& err)
{
  int fds_out[2];
  int fds_err[2];
  pipe(fds_out);
  pipe(fds_err);
  int out_copy = dup(1);
  int err_copy = dup(2);
  dup2(fds_out[1], 1);
  dup2(fds_err[1], 2);
  int res = std::system(cmd.c_str());

  close(fds_out[1]);
  close(fds_err[1]);
  dup2(out_copy, 1);
  dup2(err_copy, 2);
  out = read_fd_(fds_out[0]);
  err = read_fd_(fds_err[0]);
  close(fds_out[0]);
  close(fds_err[0]);
  close(out_copy);
  close(err_copy);
  return res;
}

std::string Command::read_fd_(int fd)
{
  std::string res;
  char buffer[1024];
  while (true)
    {
      auto len = read(fd, buffer, sizeof (buffer));
      if (len <= 0)
        break;
      res.insert(res.end(), buffer, buffer + len);
    }
  return res;
}
