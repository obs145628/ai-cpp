#pragma once

#include <array>
#include "matrix.hh"
#include "vector.hh"

class QR
{
public:

  using qr_t = std::array<Matrix, 2>;

  /**
   * Compute the QR factorization A = QR
   * A matrix of size n * m with columns of A linearly independant
   * Q orthogonal matrix of size n * m
   * R upper triangular matrix of size m * m
   * returns (Q, R)
   */
  static qr_t gram_schmidt(const Matrix& a);

  /**
   * Solve system Ax = b
   * A square matrix of size n
   * x matrix of size n
   * b matrix of size n
   * returns x
   *
   * Method:
   * Let QR = A
   * Compute y = tr(Q) * b
   * Solve Rx = y
   */
  static Vector system(const Matrix& a, const Vector& b);

  /**
   * Solve systems AX = B
   * A square matrix of size n
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
   * A square matrix of size n
   *
   * Method:
   * Solve AX = I_n
   */
  static Matrix inverse(const Matrix& a);

  /**
   * Compute the vector x that manimizes ||Ax-b||
   * A matrix of size n * m (n >= m)
   * x vector of size m
   * b vector of size n
   * returns vector x
   */
  static Vector least_squares(const Matrix& a, const Vector& b);

};
