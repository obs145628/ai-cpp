#include "math/vector.hh"
#include <cassert>
#include <cmath>
#include <utility>
#include "math/utils.hh"

const real_t Vector::DELTA = 1e-8;

Vector::Vector(std::size_t n)
  : data_(new real_t[n])
  , len_(n)
{}

Vector::Vector(const std::initializer_list<real_t>& t)
  : Vector(t.begin(), t.end())
{}

Vector::Vector(const Vector& v)
  : Vector(v.data_, v.data_ + v.len_)
{}

Vector::Vector(Vector&& v) noexcept
  : data_(v.data_)
  , len_(v.len_)
{
  v.data_ = nullptr;
}

Vector::~Vector()
{
  delete[] data_;
}

void Vector::assign(const std::initializer_list<real_t>& t)
{
  assign(t.begin(), t.end());
}

void Vector::assign(const Vector& v)
{
  assign(v.data_, v.data_ + v.len_);
}

void Vector::assign(Vector&& v) noexcept
{
  delete[] data_;
  data_ = v.data_;
  len_ = v.len_;
  v.data_ = nullptr;
}

Vector& Vector::operator=(const std::initializer_list<real_t>& t)
{
  assign(t);
  return *this;
}

Vector& Vector::operator=(const Vector& v)
{
  assign(v);
  return *this;
}

Vector& Vector::operator=(Vector&& v) noexcept
{
  assign(std::move(v));
  return *this;
}

real_t* Vector::begin()
{
  return data_;
}

real_t* Vector::end()
{
  return data_ + len_;
}

const real_t* Vector::begin() const
{
  return data_;
}

const real_t* Vector::end() const
{
  return data_ + len_;
}

std::size_t Vector::size() const
{
  return len_;
}

Grid Vector::to_row_grid() const
{
  Grid grid(1, len_);
  for (std::size_t i = 0; i < len_; ++i)
    grid.at(0, i) = std::to_string(data_[i]);
  return grid;
}

Grid Vector::to_col_grid() const
{
  Grid grid(len_, 1);
  for (std::size_t i = 0; i < len_; ++i)
    grid.at(i, 0) = std::to_string(data_[i]);
  return grid;
}

const real_t& Vector::operator[](std::size_t i) const
{
  assert(i < len_);
  return data_[i];
}

real_t& Vector::operator[](std::size_t i)
{
  assert(i < len_);
  return data_[i];
}

Vector Vector::operator+(const Vector& v) const
{
  assert(len_ == v.len_);
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] + v.data_[i];
  return res;
}

Vector Vector::operator-(const Vector& v) const
{
  assert(len_ == v.len_);
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] - v.data_[i];
  return res;
}

Vector Vector::operator*(const Vector& v) const
{
  assert(len_ == v.len_);
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] * v.data_[i];
  return res;
}

Vector Vector::operator/(const Vector& v) const
{
  assert(len_ == v.len_);
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] / v.data_[i];
  return res;
}

Vector Vector::operator-() const
{
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = -data_[i];
  return res;
}

Vector Vector::operator+(real_t x) const
{
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] + x;
  return res;
}

Vector Vector::operator-(real_t x) const
{
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] - x;
  return res;
}

Vector Vector::operator*(real_t x) const
{
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] * x;
  return res;
}

Vector Vector::operator/(real_t x) const
{
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res[i] = data_[i] / x;
  return res;
}

Vector& Vector::operator+=(const Vector&v)
{
  assert(len_ == v.len_);
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] += v.data_[i];
  return *this;
}

Vector& Vector::operator-=(const Vector&v)
{
  assert(len_ == v.len_);
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] -= v.data_[i];
  return *this;
}

Vector& Vector::operator*=(const Vector&v)
{
  assert(len_ == v.len_);
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] *= v.data_[i];
  return *this;
}

Vector& Vector::operator/=(const Vector&v)
{
  assert(len_ == v.len_);
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] /= v.data_[i];
  return *this;
}

Vector& Vector::operator+=(real_t x)
{
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] += x;
  return *this;
}

Vector& Vector::operator-=(real_t x)
{
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] -= x;
  return *this;
}

Vector& Vector::operator*=(real_t x)
{
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] *= x;
  return *this;
}

Vector& Vector::operator/=(real_t x)
{
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] /= x;
  return *this;
}

bool Vector::operator==(const Vector& v) const
{
  if (len_ != v.len_)
    return false;
  for (std::size_t i = 0; i < len_; ++i)
    if (data_[i] != v.data_[i])
      return false;
  return true;
}

bool Vector::operator!=(const Vector& v) const
{
  if (len_ != v.len_)
    return true;
  for (std::size_t i = 0; i < len_; ++i)
    if (data_[i] != v.data_[i])
      return true;
  return false;
}

real_t Vector::norm_square() const
{
  real_t res = 0;
  for (std::size_t i = 0; i < len_; ++i)
    res += data_[i] * data_[i];
  return res;
}

real_t Vector::norm() const
{
  return std::sqrt(norm_square());
}

Vector Vector::normalize() const
{
  return *this / norm();
}

real_t Vector::distance_square(const Vector& v) const
{
  assert(len_ == v.len_);
  real_t res = 0;
  for (std::size_t i = 0; i < len_; ++i)
    res += (data_[i] - v.data_[i]) * (data_[i] - v.data_[i]);
  return res;
}

real_t Vector::distance(const Vector& v)
{
  return std::sqrt(distance_square(v));
}

Vector Vector::reverse() const
{
  Vector res(len_);
  for (std::size_t i = 0; i < len_; ++i)
    res.data_[i] = data_[len_ - 1 - i];
  return res;
}

real_t Vector::dot(const Vector& v) const
{
  assert(len_ == v.len_);
  real_t res = 0;
  for (std::size_t i = 0; i < len_; ++i)
    res += data_[i] * v.data_[i];
  return res;
}

bool Vector::is_orthogonal_to(const Vector& v) const
{
  assert(len_ == v.len_);
  return is_fnull(dot(v));
}

bool Vector::is_unit() const
{
  return std::abs(1 - norm_square()) < Vector::DELTA;
}

Vector Vector::project_along(const Vector& b) const
{
  double bnorm = b.norm_square();
  double x = bnorm ? dot(b) / bnorm : 0;
  return x * b;
}


Vector Vector::project_orthogonal(const Vector& b) const
{
  return *this - project_along(b);
}



std::ostream& operator<<(std::ostream& os, const Vector& v)
{
  os << '[';
  for (std::size_t i = 0; i < v.len_; ++i)
    {
      os << v.data_[i];
      if (i + 1 < v.len_)
        os << ", ";
    }
  return os << ']';
}

Vector operator+(real_t x, const Vector& v)
{
  Vector res(v.len_);
  for (std::size_t i = 0; i < v.len_; ++i)
    res.data_[i] = x + v.data_[i];
  return res;
}

Vector operator-(real_t x, const Vector& v)
{
  Vector res(v.len_);
  for (std::size_t i = 0; i < v.len_; ++i)
    res.data_[i] = x - v.data_[i];
  return res;
}

Vector operator*(real_t x, const Vector& v)
{
  Vector res(v.len_);
  for (std::size_t i = 0; i < v.len_; ++i)
    res.data_[i] = x * v.data_[i];
  return res;
}

Vector operator/(real_t x, const Vector& v)
{
  Vector res(v.len_);
  for (std::size_t i = 0; i < v.len_; ++i)
    res.data_[i] = x / v.data_[i];
  return res;
}


bool is_null(const Vector& v)
{
  return v.norm_square() == 0;
}

bool is_fnull(const Vector& v)
{
  return v.norm_square() < Vector::DELTA;
}

bool fequals(const Vector& l, const Vector& r)
{
  return l.size() == r.size()
    && l.distance_square(r) < Vector::DELTA;
}
