#pragma once

#include "matrix.hh"
#include "vector.hh"
#include <array>

class Cholesky
{
public:

  using ldl_t = std::array<Matrix, 2>;

  /**
   * Compute the Cholesky decomposition A=Ltr(L)
   * A symetric positive-definite square matrix of size n
   * L lower triangular matrix of size n
   * returns L
   *
   * Method:
   * for j = 0 -> n - 1
   *   l_jj = sqrt(a_jj - Sum(k, 0, j - 1, l_jk^2)
   *   for i = j + 1 -> n - 1
   *     l_ij = (a_ij - Sum(k, 0, j - 1, l_ik * l_jk)) / l_jj
   */
  static Matrix ll(const Matrix& a);

  /**
   * Solve system Ax = b
   * A symetric positive-definite square matrix of size n
   * x vector of size n
   * b vector of size n
   * returns x
   *
   * Method:
   * let Ltr(L) = A
   * Ltr(L)x = b
   * let y = tr(L)x
   * Solve lower triangular system Ly = b
   * Solve upper triangular system tr(L)x = y
   */
  static Vector system(const Matrix& a, const Vector& b);

  /**
   * Solve systems AX = B
   * A symetric positive-definite square matrix of size n
   * X matrix of size n * m 
   * B matrix of size n * m
   * Return matrix x
   *
   * Method:
   * For i = 0 -> m - 1: Solve AX[i] = B[i] 
   */
  static Matrix systems(const Matrix& a, const Matrix& b);

  /**
   * Compute the inverse of A
   * A symetric positive-definite square matrix of size n
   *
   * Method:
   * Solve AX = I_n
   */
  static Matrix inverse(const Matrix& a);

  /**
   * Compute the determinant of A
   * A symetric positive-definite square matrix of size n
   * 
   * Method :
   * Let Ltr(L) = A
   * det(A) = Product(i, 0, n - 1, l_ii)^2
   */
  static double det(const Matrix& a);

  /*
   * Compute the LDL decomposition A = LDtr(L)
   * A symetric matrix of size n
   * L unit lower triangular matrix of size n
   * D Diagonal matrix of size n
   * Return {L, D}
   *
   * Method:
   * for j = 0 -> n - 1
   *   d_jj = a_jj - Sum(k, 0, j - 1, l_jk^2 * d_kk)
   *   for i = j + 1 -> n - 1
   *     l_ij = (a_ij - Sum(k, 0, j - 1, l_ik * l_jk * d_kk)) / d_jj
   */
  static ldl_t ldl(const Matrix& a);
  

};
