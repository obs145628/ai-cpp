#pragma once

#include "tensor_ops.hh"

inline Vector flatten(const Vector& x)
{
    return x;
}

inline Vector flatten(const Matrix& x)
{
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Vector::ref(x.chunk(), ptr, x.rows() * x.cols());
}

inline Vector flatten(const Tensor& x)
{
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Vector::ref(x.chunk(), ptr, x.size());
}

inline Vector reshape(const Vector& x, std::size_t size)
{
    (void) size;
    assert(size == x.size());
    return x;
}

inline Vector reshape(const Matrix& x, std::size_t size)
{
    assert(size == x.rows() * x.cols());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Vector::ref(x.chunk(), ptr, size);
}

inline Vector reshape(const Tensor& x, std::size_t size)
{
    assert(size == x.size());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Vector::ref(x.chunk(), ptr, size);
}

inline Matrix reshape(const Vector& x, std::size_t rows, std::size_t cols)
{
    assert(rows * cols == x.size());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Matrix::ref(x.chunk(), ptr, rows, cols); 
}

inline Matrix reshape(const Matrix& x, std::size_t rows, std::size_t cols)
{
    assert(rows * cols == x.rows() * x.cols());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Matrix::ref(x.chunk(), ptr, rows, cols);
}

inline Matrix reshape(const Tensor& x, std::size_t rows, std::size_t cols)
{
    assert(rows * cols == x.size());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Matrix::ref(x.chunk(), ptr, rows, cols);
}

inline Tensor reshape(const Vector& x, const Shape& shape)
{
    assert(shape.size() == x.size());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Tensor::ref(x.chunk(), ptr, shape);
}

inline Tensor reshape(const Matrix& x, const Shape& shape)
{
    assert(shape.size() == x.rows() * x.cols());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Tensor::ref(x.chunk(), ptr, shape);
}

inline Tensor reshape(const Tensor& x, const Shape& shape)
{
    assert(shape.size() == x.size());
    num_t* ptr = const_cast<num_t*>(x.begin());
    return Tensor::ref(x.chunk(), ptr, shape);
}
