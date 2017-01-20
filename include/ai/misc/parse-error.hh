#pragma once

#include <stdexcept>
#include <string>

class ParseError : public std::exception
{
public:
  ParseError(const std::string& message,
             int line = -1, int col = -1,
             const std::string& path = {});

  virtual const char* what() const noexcept override;

  const std::string& message_get() const;
  int line_get() const;
  int col_get() const;
  const std::string& path_get() const;

private:
  std::string message_;
  int line_;
  int col_;
  std::string path_;
};
