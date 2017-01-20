#pragma once

#include <array>
#include "matrix.hh"
#include "vector.hh"

class LU
{
public:

  using lu_t = std::array<Matrix, 2>;
  using plu_t = std::array<Matrix, 3>;

  /**
   * Compute the LU decomposition A = LU
   * A square matrix of size n
   * L unit lower triangular matrix of size n
   * U upper triangular matrix of size n
   * Returns (L, U)
   * This decomposition doesn't work for all matrices
   *
   * Method:
   * for j = 0 -> n - 1:
   *   for i = j + 1 -> n - 1:
   *     let pivot = a_ij / a_jj, or 0 if a_ij = a_jj = 0
   *     l_ij = pivot
   *     tr(A)[i] -= pivot * tr(A)[j]
   * return (L, A)
   */
  static lu_t lu(const Matrix& a);

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
   * for j = 0 -> n - 1:
   *   let imax = max(|A[i][j : n -1]|)
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
  static plu_t plu(const Matrix& a, int* parity = nullptr);

  /*
  template <class T>
	typename Matrix<T>::size_type
	Matrix<T>::plu_decomposition (Matrix& p, Matrix &l, Matrix& u) const
	{
		assert(rows_ == cols_);
		size_type n = rows_;
		size_type parity = 0;
		p = id (n);
		l = id (n);
		u = *this;

		for (size_type j = 0; j < n; ++j)
		{

			size_type pivot = j;
			for (size_type i = j + 1; i < n; ++i)
				if (std::abs (u.at (i, j)) > std::abs (u.at (pivot, j)))
					pivot = i;

			if (pivot != j)
			{
				++parity;
				std::swap_ranges (p.begin_row (j), p.end_row (j),
								  p.begin_row (pivot));
				std::swap_ranges (l.begin_row (j), l.end_row (j),
								  l.begin_row (pivot));
				std::swap_ranges (u.begin_row (j), u.end_row (j),
								  u.begin_row (pivot));
			}


			for (size_type i = j + 1; i < n; ++i)
			{
				T num = u.at (i, j);
				T den = u.at (j, j);
				T val = num || den ? num / den : static_cast<T> (0);
				u.at (i, j) = 0;
				for (size_type k = j + 1; k < n; ++k)
					u.at (i, k) -= val * u.at (j, k);
				l.at (i, j) = val;
			}
		}

		return parity;
	}
  */


};
