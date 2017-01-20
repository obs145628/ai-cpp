#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include "def.hh"
#include "../shell/grid.hh"

class Vector
{
public:

  static const real_t DELTA;
  
  explicit Vector(std::size_t n);
  template<class It>
  Vector(It begin, It end);
  explicit Vector(const std::initializer_list<real_t>& t);
  Vector(const Vector& v);
  Vector(Vector&& v) noexcept;
  ~Vector();

  template <class It>
  void assign(It begin, It end);
  void assign(const std::initializer_list<real_t>& t);
  void assign(const Vector& v);
  void assign(Vector&& v) noexcept;

  Vector& operator=(const std::initializer_list<real_t>& t);
  Vector& operator=(const Vector& v);
  Vector& operator=(Vector&& v) noexcept;

  real_t* begin();
  real_t* end();
  const real_t* begin() const;
  const real_t* end() const;

  std::size_t size() const;
  Grid to_row_grid() const;
  Grid to_col_grid() const;
  

  const real_t& operator[](std::size_t i) const;
  real_t& operator[](std::size_t i);

  Vector operator+(const Vector& v) const;
  Vector operator-(const Vector& v) const;
  Vector operator*(const Vector& v) const;
  Vector operator/(const Vector& v) const;
  Vector operator-() const;
  Vector operator+(real_t x) const;
  Vector operator-(real_t x) const;
  Vector operator*(real_t x) const;
  Vector operator/(real_t x) const;

  Vector& operator+=(const Vector&v);
  Vector& operator-=(const Vector&v);
  Vector& operator*=(const Vector&v);
  Vector& operator/=(const Vector&v);
  Vector& operator+=(real_t x);
  Vector& operator-=(real_t x);
  Vector& operator*=(real_t x);
  Vector& operator/=(real_t x);

  bool operator==(const Vector& v) const;
  bool operator!=(const Vector& v) const;

  real_t norm_square() const;
  real_t norm() const;
  Vector normalize() const;

  real_t distance_square(const Vector& v) const;
  real_t distance(const Vector& v);

  Vector reverse() const;

  real_t dot(const Vector& v) const;
  bool is_orthogonal_to(const Vector& v) const;

  /**
   * Check if ||v|| == 1
   */
  bool is_unit() const;

  /**
   * a, b vectors of size n
   * find vector v parallel to a
   * v = xa
   * x = a.b/b.b = a.b/||b||^2
   */
  Vector project_along(const Vector& b) const;

  /**
   * a, b vectors of size n
   * find vector v orthogonal to b
   * v = a - a.project_along(b)
   */
  Vector project_orthogonal(const Vector& b) const;

  friend std::ostream& operator<<(std::ostream& os, const Vector& v);

  friend Vector operator+(real_t x, const Vector& v);
  friend Vector operator-(real_t x, const Vector& v);
  friend Vector operator*(real_t x, const Vector& v);
  friend Vector operator/(real_t x, const Vector& v);

private:
  real_t* data_;
  std::size_t len_;
};

bool is_null(const Vector& v);
bool is_fnull(const Vector& v);
bool fequals(const Vector& l, const Vector& r);


template <class It>
Vector::Vector(It begin, It end)
  : Vector(end - begin)
{
  for (std::size_t i = 0; i < len_; ++i)
    data_[i] = begin[i];
}

template <class It>
void Vector::assign(It begin, It end)
{
  std::size_t len = end - begin;
  if (len > len_)
    {
      delete[] data_;
      data_ = new real_t[len];
    }
  len_ = len;

  for (std::size_t i = 0; i < len; ++i)
    data_[i] = begin[i];
}
