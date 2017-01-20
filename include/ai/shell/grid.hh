#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "shell-sprite.hh"

class Grid
{
public:
  Grid(std::size_t rows, std::size_t cols);

  const std::string& at(std::size_t i, std::size_t j) const;
  std::string& at(std::size_t i, std::size_t j);
  const char* fg_get(std::size_t i, std::size_t j) const;
  const char* bg_get(std::size_t i, std::size_t j) const;
  void fg_set(std::size_t i, std::size_t j, const char* fg);
  void bg_set(std::size_t i, std::size_t j, const char* bg);

  ShellSprite to_sprite() const;

  friend std::ostream& operator<<(std::ostream& is, const Grid& g);

private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<std::string> data_;
  std::vector<const char*> fgs_;
  std::vector<const char*> bgs_;

  std::size_t col_length_(std::size_t col) const;
};
