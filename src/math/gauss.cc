#include "math/gauss.hh"
#include <cassert>
#include "math/vlist.hh"

Gauss::lu_t Gauss::lu(const Matrix& a, const Vector& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.size());
  std::size_t n = a.rows();

  Matrix mk = VList::join_cols(a, b);
  Matrix l = Matrix::id(n);

  for (std::size_t k = 0; k < n; ++k)
    {
      Matrix mk1(n, n + 1);
      for (std::size_t i = 0; i < k + 1; ++i)
        for (std::size_t j = 0; j < n + 1; ++j)
          mk1.at(i, j) = mk.at(i, j);

      for (std::size_t i = k + 1; i < n; ++i)
        {
          double gik = mk.at(i, k) / mk.at(k, k);
          l.at(i, k) = gik;
          for (std::size_t j = 0; j < k + 1; ++j)
            mk1.at(i, j) = 0;
          for (std::size_t j = k + 1; j < n + 1; ++j)
            mk1.at(i, j) = mk.at(i, j) - gik * mk.at(k, j);
        }

      mk = mk1;
    }

  Matrix u = mk.region(0, 0, n, n);
  Vector b2 = VList::col_to_vec(mk, n);
  return LuRes{l, u, b2};
}

double Gauss::det_triangular(const Matrix& m)
{
  assert(m.rows() == m.cols());
  double res = 1;
  for (std::size_t i = 0; i < m.rows(); ++i)
    res *= m.at(i, i);
  return res;
}

Vector Gauss::system_upper(const Matrix& a, const Vector& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.size());
  std::size_t n = b.size();

  Vector res(n);
  for (std::size_t i = n - 1; i < n; --i)
    {
      double val = b[i];
      for (std::size_t j = i + 1; j < n; ++j)
        val -= a.at(i, j) * res[j];
      res[i] = val / a.at(i, i);
    }

  return res;
}

Matrix Gauss::systems_upper(const Matrix& a, const Matrix& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.rows());

  Matrix res(b.rows(), b.cols());
  for (std::size_t i = 0; i < b.cols(); ++i)
    {
      Vector bi = VList::col_to_vec(b, i);
      Vector xi = system_upper(a, bi);
      VList::col_set(res, i, xi);
    }

  return res;
}

Matrix Gauss::inverse_upper(const Matrix& a)
{
  assert(a.rows() == a.cols());
  return systems_upper(a, Matrix::id(a.rows()));
}

Vector Gauss::system_lower(const Matrix& a, const Vector& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.size());
  std::size_t n = b.size();

  Vector res(n);
  for (std::size_t i = 0; i < n; ++i)
    {
      double val = b[i];
      for (std::size_t j = 0; j < i; ++j)
        val -= a.at(i, j) * res[j];
      res[i] = val / a.at(i, i);
    }

  return res;
}

Matrix Gauss::systems_lower(const Matrix& a, const Matrix& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.rows());

  Matrix res(b.rows(), b.cols());
  for (std::size_t i = 0; i < b.cols(); ++i)
    {
      Vector bi = VList::col_to_vec(b, i);
      Vector xi = system_lower(a, bi);
      VList::col_set(res, i, xi);
    }

  return res;
}

Matrix Gauss::inverse_lower(const Matrix& a)
{
  assert(a.rows() == a.cols());
  return systems_lower(a, Matrix::id(a.rows()));
}
