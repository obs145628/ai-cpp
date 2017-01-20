#include "math/qr.hh"
#include <cassert>
#include "math/gauss.hh"
#include "math/vlist.hh"

QR::qr_t QR::gram_schmidt(const Matrix& a)
{
  VList::list_t coeffs;
  auto l = VList::orthogonalize(VList::mat_to_cols(a), coeffs);
  Matrix r = VList::cols_to_upper(coeffs);

  for (std::size_t i = 0; i < l.size(); ++i)
    {
      real_t norm = l[i].norm();
      l[i] /= norm;
      VList::row_set(r, i, norm * VList::row_to_vec(r, i));
    }
       
  Matrix q = VList::cols_to_mat(l);
  return {q, r};
}

Vector QR::system(const Matrix& a, const Vector& b)
{
  assert(a.rows() == a.cols());
  assert(a.rows() == b.size());

  auto decomp = gram_schmidt(a);
  Matrix q = decomp[0];
  Matrix r = decomp[1];
  Vector y = q.transpose() * b;
  Vector x = Gauss::system_upper(r, y);
  return x;
}

Matrix QR::systems(const Matrix& a, const Matrix& b)
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

Matrix QR::inverse(const Matrix& a)
{
  assert(a.rows() == a.cols());
  return systems(a, Matrix::id(a.rows()));
}

Vector QR::least_squares(const Matrix& a, const Vector& b)
{
  assert(a.rows() >= a.cols());
  assert(a.rows() == b.size());
  auto decomp = gram_schmidt(a);
  Matrix q = decomp[0];
  Matrix r = decomp[1];
  Vector y = q.transpose() * b;
  Vector x = Gauss::system_upper(r, y);
  return x;
}
