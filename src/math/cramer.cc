#include "math/cramer.hh"
#include <cassert>
#include "math/vlist.hh"


double Cramer::det(const Matrix& m)
{
  assert(m.rows() == m.cols());
  if (m.rows() == 1)
    return m.at(0, 0);
  double res = 0;

  for (std::size_t i = 0; i < m.rows(); ++i)
    {
      double coeff = i % 2 ? - m.at(i, 0) : m.at(i, 0);
      res += coeff * det(m.sub(i, 0));
    }

  return res;
}

Vector Cramer::system(const Matrix& a, const Vector& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.size());
  std::size_t n = a.rows();

  Vector res(n);
  double denum = det(a);
  for (std::size_t i = 0; i < n; ++i)
    {
      Matrix ai = a;
      VList::col_set(ai, i, b);
      res[i] = det(ai) / denum ;
    }

  return res;
}


Matrix Cramer::systems(const Matrix& a, const Matrix& b)
{
  assert(a.rows() == a.cols());
  assert(a.cols() == b.rows());
  assert(b.rows() == b.cols());
  std::size_t n = a.rows();

  Matrix res(n, n);
  for (std::size_t i = 0; i < n ; ++i)
    {
      Vector col = Cramer::system(a, VList::col_to_vec(b, i));
      VList::col_set(res, i, col);
    }

  return res;
}

/**
 * Compute the cofactor matrix C of A
 * A matrix of size n * n
 * return C matrix of size n * n
 *
 * Method :
 * c_ij = (-1)^(i+j) det(A_ij)
 * A_ij : matrix formed by A without the i-th row and the j-th column
 */
Matrix Cramer::cofactor(const Matrix& a)
{
  assert(a.rows() == a.cols());
  std::size_t n = a.rows();
  if (n == 1)
    return Matrix::id(1);
  Matrix res(n, n);

  for (std::size_t i = 0; i < n; ++i)
    for (std::size_t j = 0; j < n; ++j)
      {
        double sign = (i + j) % 2 == 0 ? 1 : -1;
        res.at(i, j) = sign * det(a.sub(i, j));
      }

  return res;
}

Matrix Cramer::adj(const Matrix& a)
{
  return cofactor(a).transpose();
}

/**
 * Compute the inverse of A
 * A matrix of size n * n
 * return matrix of size n * n
 * Undefined behaviour when det(A) = 0
 * A^-1 = adj(A) / det(A)
 */
Matrix Cramer::inverse(const Matrix& a)
{
  return adj(a) / det(a);
}
