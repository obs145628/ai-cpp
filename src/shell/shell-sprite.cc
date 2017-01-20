#include "shell/shell-sprite.hh"
#include <cassert>
#include <fstream>

ShellSprite::ShellSprite(std::size_t width, std::size_t height,
                         const data_t& data)
  : width_(width)
  , height_(height)
  , data_(data)
{
  assert(width_);
  assert(height_);
  assert(width * height == data_.size());
}

std::size_t ShellSprite::width_get() const
{
  return width_;
}

std::size_t ShellSprite::height_get() const
{
  return height_;
}

const ShellSprite::data_t& ShellSprite::data_get() const
{
  return data_;
}


const ShellSprite::Pixel&
ShellSprite::at(std::size_t x, std::size_t y) const
{
  assert(x < width_ && y < height_);
  return data_[y * width_ + x];
}

ShellSprite ShellSprite::load(std::istream& is)
{
  std::string type;
  std::getline(is, type);
  assert(type == "mono");
  return load_mono_(is);
}

ShellSprite ShellSprite::load(const std::string& path)
{
  std::ifstream is(path);
  return load(is);
}

ShellSprite ShellSprite::load_mono_(std::istream& is)
{
  std::string w_str;
  std::string h_str;
  std::getline(is, w_str);
  std::getline(is, h_str);
  std::size_t width = std::strtol(w_str.c_str(), nullptr, 10);
  std::size_t height = std::strtol(h_str.c_str(), nullptr, 10);
  data_t data;

  for (std::size_t i = 0; i < height; ++i)
    {
      assert(is.good());
      std::string line;
      std::getline(is, line);
      assert(line.size() == width);
      for (std::size_t j = 0; j < width; ++j)
        data.push_back(Pixel{line[j]});
    }

  return ShellSprite{width, height, data};
}
