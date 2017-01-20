#pragma once

#include "matrix.hh"
#include "vector.hh"

class Cramer
{
public:

  /**
   * Basic det() used for cramer operations
   * M matrix of size n * n
   * forall j in [0, n[:
   * det(M) = Sum(i, 0, n - 1, (-1)^(i + j) m_ij det(M_ij))
   * M_ij : matrix formed by M without the i-th row and the j-th column
   */
  static double det(const Matrix& m);

  /**
   * Solve a system Ax = b with Cramer's rule
   * A Square matrix of size n * n
   * b vector of size n
   * return vector x of size n
   *
   * Method:
   * for i: 0 -> n -1
   * x_i = det(A_i) / det(A)
   * A_i: matrix formed by A with the i-th column replaced by b
   */
  static Vector system(const Matrix& a, const Vector& b);

  /**
   * Solve a system AX = B
   * A Square matrix of size n * n
   * B square matrix of size n * n
   * return square matrix X of size n * n
   *
   * Sole m systems with Cramer's rule
   */
  static Matrix systems(const Matrix& a, const Matrix& b);

  /**
   * Compute the cofactor matrix C of A
   * A matrix of size n * n
   * return C matrix of size n * n
   *
   * Method :
   * c_ij = (-1)^(i+j) det(A_ij)
   * A_ij : matrix formed by A without the i-th row and the j-th column
   */
  static Matrix cofactor(const Matrix& a);

  /**
   * Compute the adjugate matrix of A
   * A matrix of size n * n
   * return matrix of size n * n
   * adj(A) = transpose(cofactor(a))
   */
  static Matrix adj(const Matrix& a);

  /**
   * Compute the inverse of A
   * A matrix of size n * n
   * return matrix of size n * n
   * Undefined behaviour when det(A) = 0
   * A^-1 = adj(A) / det(A)
   */
  static Matrix inverse(const Matrix& a);

};
