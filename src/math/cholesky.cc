#include "math/cholesky.hh"
#include <cassert>
#include <cmath>
#include "math/gauss.hh"
#include "math/vlist.hh"

Matrix Cholesky::ll(const Matrix& a)
{
  assert(a.rows() == a.cols());
  std::size_t n = a.rows();
  auto l = Matrix::null(n, n);

  for (std::size_t j = 0; j < n; ++j)
    {
      double val = a.at(j, j);
      for (std::size_t k = 0; k < j; ++k)
        val -= l.at(j, k) * l.at(j, k);
      l.at(j, j) = std::sqrt(val);

      for (std::size_t i = j + 1; i < n; ++i)
        {
          double val = a.at(i, j);
          for (std::size_t k = 0; k < j; ++k)
            val -= l.at(i, k) * l.at(j, k);
          l.at(i, j) = val / l.at(j, j);
        }
    }

  return l;
}

Vector Cholesky::system(const Matrix& a, const Vector& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.size());

  Matrix l = ll(a);
  Vector y = Gauss::system_lower(l, b);
  Vector x = Gauss::system_upper(l.transpose(), y);
  return x;
}

Matrix Cholesky::systems(const Matrix& a, const Matrix& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.rows());

  Matrix res(b.rows(), b.cols());
  for (std::size_t i = 0; i < b.cols(); ++i)
    {
      Vector bi = VList::col_to_vec(b, i);
      Vector xi = system(a, bi);
      VList::col_set(res, i, xi);
    }

  return res;
}

Matrix Cholesky::inverse(const Matrix& a)
{
  assert(a.rows() == a.cols());
  return systems(a, Matrix::id(a.rows()));
}

double Cholesky::det(const Matrix& a)
{
  assert(a.rows() == a.cols());
  Matrix l = ll(a);
  double res = 1;
  for (std::size_t i = 0; i < a.rows(); ++i)
    res *= l.at(i, i);
  return res * res;
}

Cholesky::ldl_t Cholesky::ldl(const Matrix& a)
{
  assert(a.rows() == a.cols());
  std::size_t n = a.rows();
  auto l = Matrix::id(n);
  auto d = Matrix::null(n, n);

  for (std::size_t j = 0; j < n; ++j)
    {
      double val = a.at(j, j);
      for (std::size_t k = 0; k < j; ++k)
        val -= l.at(j, k) * l.at(j, k) * d.at(k, k);
      d.at(j, j) = val;

      for (std::size_t i = j + 1; i < n; ++i)
        {
          double val = a.at(i, j);
          for (std::size_t k = 0; k < j; ++k)
            val -= l.at(i, k) * l.at(j, k) * d.at(k, k);
          l.at(i, j) = val / d.at(j, j);
        }
    }

  return {l, d};
}
