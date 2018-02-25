#pragma once

#include "vector.hh"
#include "matrix.hh"

Vector solve_lower(const Matrix& m, const Vector& b);
Vector solve_upper(const Matrix& m, const Vector& b);

Matrix transpose(const Matrix& m);
Matrix inverse(const Matrix& m);


bool plu_decomposition(const Matrix& m, Matrix& p, Matrix& l, Matrix& u,
                       std::vector<std::size_t>& pv,
                       bool& even_permuts);

Vector plu_solve(const Matrix& m, const Vector& b);
Matrix plu_solve(const Matrix& m, const Matrix& b);
Matrix plu_inverse(const Matrix& m);
