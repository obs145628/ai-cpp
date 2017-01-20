#include "shell/grid.hh"
#include <cassert>
#include <cmath>
#include "shell/shell.hh"

Grid::Grid(std::size_t rows, std::size_t cols)
  : rows_(rows)
  , cols_(cols)
  , data_(rows * cols)
  , fgs_(rows * cols, Shell::FG_DEFAULT)
  , bgs_(rows * cols, Shell::BG_DEFAULT)
{}

const std::string& Grid::at(std::size_t i, std::size_t j) const
{
  assert(i < rows_);
  assert(j < cols_);
  return data_[i * cols_ + j];
}

std::string& Grid::at(std::size_t i, std::size_t j)
{
  assert(i < rows_);
  assert(j < cols_);
  return data_[i * cols_ + j];
}

const char* Grid::fg_get(std::size_t i, std::size_t j) const
{
  assert(i < rows_);
  assert(j < cols_);
  return fgs_[i * cols_ + j];
}
const char* Grid::bg_get(std::size_t i, std::size_t j) const
{
  assert(i < rows_);
  assert(j < cols_);
  return bgs_[i * cols_ + j];
}

void Grid::fg_set(std::size_t i, std::size_t j, const char* fg)
{
  assert(i < rows_);
  assert(j < cols_);
  fgs_[i * cols_ + j] = fg;
}

void Grid::bg_set(std::size_t i, std::size_t j, const char* bg)
{
  assert(i < rows_);
  assert(j < cols_);
  bgs_[i * cols_ + j] = bg;
}

ShellSprite Grid::to_sprite() const
{
  std::size_t width = cols_ + 1;
  std::vector<std::size_t> lens(cols_);
  for (std::size_t i = 0; i < cols_; ++i)
    {
      lens[i] = col_length_(i);
      width += lens[i];
    }

  
  std::size_t height = 2 * rows_ + 1;
  ShellSprite::data_t data;

  for (std::size_t r = 0; r <= rows_; ++r)
    {
      data.emplace_back('+', Shell::FG_GREEN);
      for (std::size_t i = 0; i < cols_; ++i)
        {
          for (std::size_t j = 0; j < lens[i]; ++j)
            data.emplace_back('-', Shell::FG_BLUE);
          data.emplace_back('+', Shell::FG_GREEN);
        }

      if (r == rows_)
        break;

      data.emplace_back('|', Shell::FG_BLUE);
      for (std::size_t i = 0; i < cols_; ++i)
        {
          const auto& elem = at(r, i);
          for (std::size_t j = 0; j < elem.size(); ++j)
            data.emplace_back(elem[j], fg_get(r, i), bg_get(r, i));

          for (std::size_t j = 0; j < lens[i] - elem.size(); ++j)
            data.emplace_back(' ');
          data.emplace_back('|', Shell::FG_BLUE);
        }
    }

  return ShellSprite{width, height, data};
}

std::size_t Grid::col_length_(std::size_t col) const
{
  std::size_t res = 0;
  for (std::size_t i = 0; i < rows_; ++i)
    res = std::max(res, at(i, col).size());
  return res;
}

std::ostream& operator<<(std::ostream& os, const Grid& g)
{
  std::vector<std::size_t> lens(g.cols_);
  for (std::size_t i = 0; i < g.cols_; ++i)
    lens[i] = g.col_length_(i);

  for (std::size_t r = 0; r <= g.rows_; ++r)
    {
      os << '+';
      for (std::size_t i = 0; i < g.cols_; ++i)
        {
          for (std::size_t j = 0; j < lens[i]; ++j)
            os << '-';
          os << '+';
        }
      os << '\n';

      if (r == g.rows_)
        break;

      os << '|';
      for (std::size_t i = 0; i < g.cols_; ++i)
        {
          const auto& elem = g.at(r, i);
          os << elem;
          for (std::size_t j = 0; j < lens[i] - elem.size(); ++j)
            os << ' ';
          os << '|';
        }
      os << '\n';

      
    }

  return os;
}
