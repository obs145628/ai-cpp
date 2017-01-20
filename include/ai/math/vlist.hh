#pragma once

#include <iostream>
#include <vector>
#include "matrix.hh"
#include "vector.hh"

class VList
{
public:
  using list_t = std::vector<Vector>;

  static Vector row_to_vec(const Matrix& m, std::size_t row);
  static Vector col_to_vec(const Matrix& m, std::size_t col);

  static list_t mat_to_rows(const Matrix& m);
  static list_t mat_to_cols(const Matrix& m);

  static void row_set(Matrix& m, std::size_t i, const Vector& v);
  static void col_set(Matrix& m, std::size_t i, const Vector& v);

  static Matrix rows_to_mat(const list_t& list);
  static Matrix cols_to_mat(const list_t& list);

  static Matrix rows_to_upper(const list_t& list);
  static Matrix cols_to_upper(const list_t& list);

  static Matrix join_cols(const Matrix& m, const Vector& v);

  static void swap_row(Matrix& m, std::size_t a, std::size_t b);
  static void swap_col(Matrix& m, std::size_t a, std::size_t b);

  /**
   * Check if l is an orthogonal set
   * i.e all vectors in l are orthogonals to all others vectors in l
   */
  static bool is_orthogonal(const list_t& l);

  /**
   * Check if l in an orthogonal set
   * and if l1,...,ln are units vectors
   */
  static bool is_orthonormal(const list_t& l);

  static list_t normalize(const list_t& l);

  /**
   * v vector of size n
   * l list of vectors of size n
   * Returns the projection of v orthogonal to all vectors in l
   */
  static Vector project_orthogonal(const Vector& v, const list_t& l);

  /**
   * compute the coeffs vector a
   * v = [l|project(v)] * a
   */
  static Vector project_orthogonal(const Vector& v, const list_t& l,
                                   Vector& coeffs);

  /**
   * l set of vectors v1...vn
   * compute l* an orthogonal set of vectors v1*...vn*
   * span{l} = span{l*}
   * return l*
   */
  static list_t orthogonalize(const list_t& l);

  /**
   * compute the coefs vectors r
   * [v1..vn] = [v1*...vn*] [r1...rn]
   */
  static list_t orthogonalize(const list_t& l, list_t& coeffs);

  /**
   * Compute a basis for Span(l)
   */
  static list_t basis_get(const list_t& l);

  /**
   * Compute the Null(A)
   */
  static list_t nullspace_get(const Matrix& a);
};

std::ostream& operator<<(std::ostream& os, const VList::list_t& list);
