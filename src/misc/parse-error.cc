#include "misc/parse-error.hh"

ParseError::ParseError(const std::string& message,
                       int line, int col,
                       const std::string& path)
  : message_(message)
  , line_(line)
  , col_(col)
  , path_(path)
{}

const char* ParseError::what() const noexcept
{
  return message_.c_str();
}

const std::string& ParseError::message_get() const
{
  return message_;
}

int ParseError::line_get() const
{
  return line_;
}

int ParseError::col_get() const
{
  return col_;
}

const std::string& ParseError::path_get() const
{
  return path_;
}
