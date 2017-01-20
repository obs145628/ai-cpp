#include "math/lu.hh"
#include <cassert>
#include <cmath>
#include "math/vlist.hh"

LU::lu_t LU::lu(const Matrix& a)
{
  assert(a.rows() == a.cols());
  std::size_t n = a.rows();
  auto l = Matrix::id(n);
  auto u = a;

  for (std::size_t j = 0; j < n; ++j)
    for (std::size_t i = j + 1; i < n; ++i)
      {
        double pivot = !u.at(i, j) && !u.at(j, j) ? 0
          : u.at(i, j) / u.at(j, j);
        l.at(i, j) = pivot;
        auto ui = VList::row_to_vec(u, i);
        auto uj = VList::row_to_vec(u, j);
        VList::row_set(u, i, ui - pivot * uj);
      }

  return {l, u};
}

  /**
   * Compute the PLU Decomposition PA = LU
   * A square matrix of size n
   * P permutation matrix of size n
   * L unit lower triangular matrix of size n
   * U upper triangular matrix of size n
   * if parity != nullptr, pointed value set to numbers of permutations
   * returns (P, L, U)
   *
   * Method:
   * parity = 0
   * for j = 0 -> n - 1:
   *   let imax = max(|A[j][j : n - 1]|)
   *   if imax != j:
   *     ++parity
   *     swap(tr(P)[j], tr(P)[imax])
   *     swap(tr(L)[j], tr(L)[imax])
   *     swap(tr(A)[j], tr(A)[imax])
   *   for i = j + 1 -> n - 1:
   *     let pivot = a_ij / a_jj, or 0 if a_ij = a_jj = 0
   *     l_ij = pivot
   *     tr(A)[i] -= pivot * tr(A)[j]
   * return (P, L, A)
   */
LU::plu_t LU::plu(const Matrix& a, int* parity)
{
  assert(a.rows() == a.cols());
  std::size_t n = a.rows();
  auto p = Matrix::id(n);
  auto l = Matrix::id(n);
  auto u = a;
  int par = 0;

  for (std::size_t j = 0; j < n; ++j)
    {

      std::size_t imax = j;
      for (std::size_t i = j + 1; i < n; ++i)
        if (std::abs(u.at(i, j)) > std::abs(u.at(imax, j)))
          imax = i;

      if (imax != j)
        {
          ++par;
          VList::swap_row(p, j, imax);
          //VList::swap_row(l, j, imax);
          VList::swap_row(u, j, imax);
        }
      
      for (std::size_t i = j + 1; i < n; ++i)
        {
          double pivot = !u.at(i, j) && !u.at(j, j) ? 0
            : u.at(i, j) / u.at(j, j);

          /*
          u.at(i, j) = 0;
          for (std::size_t k = j + 1; k < n; ++k)
            u.at(i, k) -= pivot * u.at(j, k);
          l.at(i, j) = pivot;
          */
          l.at(i, j) = pivot;
          auto ui = VList::row_to_vec(u, i);
          auto uj = VList::row_to_vec(u, j);
          VList::row_set(u, i, ui - pivot * uj);
        }
    }

  if (parity)
    *parity = par;
  return {p, l, u};
}
