#pragma once

#include "matrix.hh"
#include "vector.hh"

class Gauss
{
public:

  struct LuRes
  {
    const Matrix l;
    const Matrix u;
    const Vector b;
    LuRes(const Matrix& l, const Matrix& u, const Vector& b)
      : l(l)
      , u(u)
      , b(b)
    {}
  };

  using lu_t = LuRes;

  /**
   * Ax = b
   * A matrix of size n * n
   * b vector of size n
   * Factorize A = LU
   * Transorm equation to Ux = b'
   * L unit lower triangular matrix of size n * n
   * U upper triangular matrix of size n * n
   * b' vector of size n
   * returns (L, U, b')
   *
   * Method:
   * Let M_0 = A|b
   * for k = 0 -> n - 1: build M_k+1 from M_k
   * for i = k + 1 -> n - 1: l_ik = Coeff g_ik = m_k_ik / m_k_kk 
   * for i = 0 -> k, j = 0 -> n: m_k+1_ij = m_k_ij
   * for i = k + 1 -> n - 1, j = 0 -> k: m_k+1_ij = 0
   * for i = k + 1 -> n - 1, j = k + 1 -> n: m_k+1_ij = m_k_ij - g_ik * m_k_kj
   * U = M_n[0...n-1]
   * b' = M_n[n]
   *
   */
  static lu_t lu(const Matrix& a, const Vector& b);

  /**
   * Compute det(A)
   * A upper or lower triangular matrix of size n
   * det(A) = Product(i, 0, n - 1, a_ii)
   */
  static double det_triangular(const Matrix& m);

  /**
   * Solve system Ax = b
   * A upper triangular matrix of size n * n
   * x vector of size n
   * b vector of size n
   * Return vector x
   * Undefined behaviour when there is a 0 in the diagonal
   *
   * Method:
   * For i = n - 1 -> 0: x_i = b_i - Sum(j, i + 1, n - 1, a_ij*x_j)/a_ii
   */
  static Vector system_upper(const Matrix& a, const Vector& b);
  
  /**
   * Solve systems AX = B
   * A upper triangular matrix of size n
   * X matrix of size n * m 
   * B matrix of size n * m
   * Return matrix x
   * Undefined behaviour when there is a 0 in the diagonal
   *
   * Method:
   * For i = 0 -> m - 1: Solve AX[i] = B[i] 
   */
  static Matrix systems_upper(const Matrix& a, const Matrix& b);

  /**
   * Compute the inverse of A
   * A upper triangular matrix of size n
   * Undefined behaviour when there is a 0 in the diagonal
   *
   * Method:
   * Solve AX = I_n
   */
  static Matrix inverse_upper(const Matrix& a);

  /**
   * Solve system Ax = b
   * A lower triangular matrix of size n * n
   * x vector of size n
   * b vector of size n
   * Return vector x
   * Undefined behaviour when there is a 0 in the diagonal
   *
   * Method:
   * For i = 0 -> n - 1: x_i = b_i - Sum(j, 0, i - 1, a_ij*x_j)/a_ii
   */
  static Vector system_lower(const Matrix& a, const Vector& b);
  
  /**
   * Solve systems AX = B
   * A lower triangular matrix of size n
   * X matrix of size n * m 
   * B matrix of size n * m
   * Return matrix x
   * Undefined behaviour when there is a 0 in the diagonal
   *
   * Method:
   * For i = 0 -> m - 1: Solve AX[i] = B[i] 
   */
  static Matrix systems_lower(const Matrix& a, const Matrix& b);

  /**
   * Compute the inverse of A
   * A lower triangular matrix of size n
   * Undefined behaviour when there is a 0 in the diagonal
   *
   * Method:
   * Solve AX = I_n
   */
  static Matrix inverse_lower(const Matrix& a);

};
