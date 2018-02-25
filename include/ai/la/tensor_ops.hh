#pragma once

#include "vector.hh"
#include "matrix.hh"
#include "tensor.hh"

Vector flatten(const Vector& x);
Vector flatten(const Matrix& x);
Vector flatten(const Tensor& x);

Vector reshape(const Vector& x, std::size_t size);
Vector reshape(const Matrix& x, std::size_t size);
Vector reshape(const Tensor& x, std::size_t size);

Matrix reshape(const Vector& x, std::size_t rows, std::size_t cols);
Matrix reshape(const Matrix& x, std::size_t rows, std::size_t cols);
Matrix reshape(const Tensor& x, std::size_t rows, std::size_t cols);

Tensor reshape(const Vector& x, const Shape& shape);
Tensor reshape(const Matrix& x, const Shape& shape);
Tensor reshape(const Tensor& x, const Shape& shape);

#include "tensor_ops.hxx"
