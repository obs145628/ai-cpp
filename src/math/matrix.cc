#include "math/matrix.hh"
#include <cmath>
#include <utility>

const real_t Matrix::DELTA = 1e-8;

Matrix Matrix::id(std::size_t n)
{
  assert(n);
  Matrix res(n, n);
  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      res.at(i, j) = i == j;
  return res;
}

Matrix Matrix::null(std::size_t rows, std::size_t cols)
{
  Matrix res(rows, cols);
  for (std::size_t i = 0; i < rows; ++i)
    for (std::size_t j = 0; j < cols; ++j)
      res.at(i, j) = 0;
  return res;
}

Matrix::Matrix(std::size_t rows, std::size_t cols)
  : data_(new real_t[rows * cols])
  , rows_(rows)
  , cols_(cols)
{}

Matrix::Matrix(std::size_t rows, std::size_t cols,
               const std::initializer_list<real_t>& t)
  : Matrix(rows, cols, t.begin(), t.end())
{}

Matrix::Matrix(const Matrix& m)
  : Matrix(m.rows_, m.cols_,
           m.data_, m.data_ + m.rows_ * m.cols_)
{}

Matrix::Matrix(Matrix&& m) noexcept
  : data_(m.data_)
  , rows_(m.rows_)
  , cols_(m.cols_)
{
  m.data_ = nullptr;
}

Matrix::~Matrix()
{
  delete[] data_;
}


void Matrix::assign(std::size_t rows, std::size_t cols,
                    const std::initializer_list<real_t>& t)
{
  assign(rows, cols, t.begin(), t.end());
}

void Matrix::assign(const Matrix& m)
{
  assign(m.rows_, m.cols_,
         m.data_, m.data_ + m.rows_ * m.cols_);
}

void Matrix::assign(Matrix&& m) noexcept
{
  delete[] data_;
  data_ = m.data_;
  rows_ = m.rows_;
  cols_ = m.cols_;
  m.data_ = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m)
{
  assign(m);
  return *this;
}
Matrix& Matrix::operator=(Matrix&& m) noexcept
{
  assign(std::move(m));
  return *this;
}

real_t* Matrix::begin()
{
  return data_;
}

real_t* Matrix::end()
{
  return data_ + rows_ * cols_;
}

const real_t* Matrix::begin() const
{
  return data_;
}

const real_t* Matrix::end() const
{
  return data_ + rows_ * cols_;
}

std::size_t Matrix::rows() const
{
  return rows_;
}

std::size_t Matrix::cols() const
{
  return cols_;
}

Grid Matrix::to_grid() const
{
  Grid grid(rows_, cols_);
  for (std::size_t i = 0; i < rows_; ++i)
    for (std::size_t j = 0; j < cols_; ++j)
      grid.at(i, j) = std::to_string(at(i, j));
  return grid;
}

const real_t& Matrix::at(std::size_t i, std::size_t j) const
{
  assert(i < rows_);
  assert(j < cols_);
  return data_[i * cols_ + j];
}

real_t& Matrix::at(std::size_t i, std::size_t j)
{
  assert(i < rows_);
  assert(j < cols_);
  return data_[i * cols_ + j];
}

Matrix Matrix::operator+(const Matrix& m) const
{
  assert(rows_ == m.rows_);
  assert(cols_ == m.cols_);
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = data_[i] + m.data_[i];
  return res;
}

Matrix Matrix::operator-(const Matrix& m) const
{
  assert(rows_ == m.rows_);
  assert(cols_ == m.cols_);
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = data_[i] - m.data_[i];
  return res;
}


Matrix Matrix::operator*(const Matrix& m) const
{
  assert(cols_ == m.rows_);

  Matrix res(rows_, m.cols_);
  for (std::size_t i = 0; i < rows_; ++i)
    for (std::size_t j = 0; j < m.cols_; ++j)
      {
        double val = 0;
        for (std::size_t k = 0; k < cols_; ++k)
          val += at(i, k) * m.at(k, j);
        res.at(i, j) = val;
      }

  return res;
}

Matrix Matrix::operator-() const
{
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = - data_[i];
  return res;
}

Matrix Matrix::operator+(real_t x) const
{
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = data_[i] + x;
  return res;
}

Matrix Matrix::operator-(real_t x) const
{
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = data_[i] - x;
  return res;
}

Matrix Matrix::operator*(real_t x) const
{
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = data_[i] * x;
  return res;
}

Matrix Matrix::operator/(real_t x) const
{
  Matrix res(rows_, cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res.data_[i] = data_[i] / x;
  return res;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
  assert(rows_ == m.rows_);
  assert(cols_ == m.cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    data_[i] += m.data_[i];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
  assert(rows_ == m.rows_);
  assert(cols_ == m.cols_);
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    data_[i] -= m.data_[i];
  return *this;
}


Matrix& Matrix::operator+=(real_t x)
{
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    data_[i] += x;
  return *this;
}

Matrix& Matrix::operator-=(real_t x)
{
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    data_[i] -= x;
  return *this;
}

Matrix& Matrix::operator*=(real_t x)
{
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    data_[i] *= x;
  return *this;
}

Matrix& Matrix::operator/=(real_t x)
{
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    data_[i] /= x;
  return *this;
}

bool Matrix::operator==(const Matrix& m) const
{
  if (rows_ != m.rows_ || cols_ != m.cols_)
    return false;

  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    if (data_[i] != m.data_[i])
      return false;

  return true;
}

bool Matrix::operator!=(const Matrix& m) const
{
  if (rows_ != m.rows_ || cols_ != m.cols_)
    return true;

  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    if (data_[i] != m.data_[i])
      return true;

  return false;
}

real_t Matrix::norm_square() const
{
  real_t res = 0;
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res += data_[i] * data_[i];
  return res;
}

real_t Matrix::norm() const
{
  return std::sqrt(norm_square());
}

real_t Matrix::distance_square(const Matrix& m) const
{
  assert(rows_ == m.rows_);
  assert(cols_ == m.cols_);
  real_t res = 0;
  for (std::size_t i = 0; i < rows_ * cols_; ++i)
    res += (data_[i] - m.data_[i]) * (data_[i] - m.data_[i]);
  return res;
}

real_t Matrix::distance(const Matrix& m)
{
  return std::sqrt(distance_square(m));
}

Matrix Matrix::transpose() const
{
  Matrix res(cols_, rows_);
  for (std::size_t i = 0; i < cols_; ++i)
    for (std::size_t j = 0; j < rows_; ++j)
      res.at(i, j) = at(j, i);
  return res;
}

Matrix Matrix::sub(std::size_t i, std::size_t j) const
{
  assert(i < rows_);
  assert(j < cols_);

  Matrix res(rows_ - 1, cols_ - 1);
  for (std::size_t i0 = 0; i0 < rows_ - 1; ++i0)
    for (std::size_t j0 = 0; j0 < cols_ - 1; ++j0)
      res.at(i0, j0) = at(i0 + (i0 >= i), j0 + (j0 >= j));

  return res;
}

Matrix Matrix::region(std::size_t i, std::size_t j,
                      std::size_t rows, std::size_t cols) const
{
  assert(i < rows_);
  assert(j < cols_);
  assert(i + rows <= rows_);
  assert(j + cols <= cols_);

  Matrix res(rows, cols);
  for (std::size_t i0 = 0; i0 < rows; ++i0)
    for (std::size_t j0 = 0; j0 < cols; ++j0)
      res.at(i0, j0) = at(i + i0, j +j0);

  return res;
}


std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
  return os << m.to_grid();
}

bool is_null(const Matrix& m)
{
  return m.norm_square() == 0;
}
bool is_fnull(const Matrix& m)
{
  return m.norm_square() < Matrix::DELTA;
}
bool fequals(const Matrix& l, const Matrix& r)
{
  return l.rows() == r.rows() && l.cols() == r.cols()
    && l.distance_square(r) < Matrix::DELTA;
}


Vector operator*(const Matrix& m, const Vector& v)
{
  assert(m.cols_ == v.size());
  Vector res(m.rows_);
  for (std::size_t i = 0; i < m.rows_; ++i)
    {
      double val = 0;
      for (std::size_t k = 0; k < m.cols_; ++k)
        val += m.at(i, k) * v[k];
      res[i] = val;
    }

  return res;
}

Vector operator*(const Vector& v, const Matrix& m)
{
  assert(v.size() == m.rows_);
  Vector res(m.cols_);
  for (std::size_t i = 0; i < m.cols_; ++i)
    {
      double val = 0;
      for (std::size_t k = 0; k < m.rows_; ++k)
        val += v[k] * m.at(k, i);
      res[i] = val;
    }

  return res;
}

Matrix operator*(const Vector& u, const Vector& v)
{
  Matrix res(u.size(), v.size());
  for (std::size_t i = 0; i < u.size(); ++i)
    for (std::size_t j = 0; j < v.size(); ++j)
      res.at(i, j) = u[i] * v[j];

  return res;
}
