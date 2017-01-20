#pragma once

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include "def.hh"
#include "vector.hh"
#include "../shell/grid.hh"


class Matrix
{
public:

  static const real_t DELTA;

  static Matrix id(std::size_t n);
  static Matrix null(std::size_t rows, std::size_t cols);
  
  Matrix(std::size_t rows, std::size_t cols);
  template<class It>
  Matrix(std::size_t rows, std::size_t cols,
         It begin, It end);
  Matrix(std::size_t rows, std::size_t cols,
         const std::initializer_list<real_t>& t);
  Matrix(const Matrix& m);
  Matrix(Matrix&& m) noexcept;
  ~Matrix();

  template <class It>
  void assign(std::size_t rows, std::size_t cols,
              It begin, It end);
  void assign(std::size_t rows, std::size_t cols,
              const std::initializer_list<real_t>& t);
  void assign(const Matrix& m);
  void assign(Matrix&& m) noexcept;

  Matrix& operator=(const Matrix& m);
  Matrix& operator=(Matrix&& m) noexcept;

  real_t* begin();
  real_t* end();
  const real_t* begin() const;
  const real_t* end() const;

  std::size_t rows() const;
  std::size_t cols() const;
  Grid to_grid() const;

  const real_t& at(std::size_t i, std::size_t j) const;
  real_t& at(std::size_t i, std::size_t j);

  Matrix operator+(const Matrix& m) const;
  Matrix operator-(const Matrix& m) const;
  Matrix operator*(const Matrix& m) const;
  Matrix operator-() const;
  Matrix operator+(real_t x) const;
  Matrix operator-(real_t x) const;
  Matrix operator*(real_t x) const;
  Matrix operator/(real_t x) const;

  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator+=(real_t x);
  Matrix& operator-=(real_t x);
  Matrix& operator*=(real_t x);
  Matrix& operator/=(real_t x);

  bool operator==(const Matrix& m) const;
  bool operator!=(const Matrix& m) const;

  real_t norm_square() const;
  real_t norm() const;

  real_t distance_square(const Matrix& m) const;
  real_t distance(const Matrix& m);

  Matrix transpose() const;
  Matrix sub(std::size_t i, std::size_t j) const;
  Matrix region(std::size_t i, std::size_t j,
                std::size_t rows, std::size_t cols) const;

  friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

  friend Vector operator*(const Matrix& m, const Vector& v);
  friend Vector operator*(const Vector& v, const Matrix& m);
  friend Matrix operator*(const Vector& u, const Vector& v);

private:
  real_t* data_;
  std::size_t rows_;
  std::size_t cols_;
};

bool is_null(const Matrix& m);
bool is_fnull(const Matrix& m);
bool fequals(const Matrix& l, const Matrix& r);


template<class It>
Matrix::Matrix(std::size_t rows, std::size_t cols,
               It begin, It end)
  : Matrix(rows, cols)
{
  std::size_t len = end - begin;
  assert(len == rows * cols);
  for (std::size_t i = 0; i < rows * cols; ++i)
    data_[i] = begin[i];
}

template <class It>
void Matrix::assign(std::size_t rows, std::size_t cols,
                    It begin, It end)
{
  rows_ = rows;
  cols_ = cols;
  std::size_t len = end - begin;
  assert(len == rows * cols);
  for (std::size_t i = 0; i < rows * cols; ++i)
    data_[i] = begin[i];
}
