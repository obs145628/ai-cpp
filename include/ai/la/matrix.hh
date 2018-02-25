#pragma once

#include <cstddef>
#include <iostream>
#include <vector>
#include "fwd.hh"
#include "vector.hh"
#include "real-chunk.hh"

class Matrix
{
public:

    Matrix();
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(std::size_t rows, std::size_t cols,
           const std::initializer_list<num_t>& vals);

    template <class It>
    Matrix(std::size_t rows, std::size_t cols, It begin, It end);

    Matrix(const Matrix& m);
    Matrix(Matrix&& m);
    ~Matrix();

    Matrix& operator=(const Matrix& m);
    Matrix& operator=(Matrix&& m);

    void assign(std::size_t rows, std::size_t cols);

    num_t* begin();
    const num_t* begin() const;
    num_t* end();
    const num_t* end() const;

    std::size_t rows() const;
    std::size_t cols() const;
    Shape shape() const;
    RealChunk* chunk() const;
    
    num_t& operator()(std::size_t row, std::size_t col);
    const num_t& operator()(std::size_t row, std::size_t col) const;
    num_t& at(std::size_t row, std::size_t col);
    const num_t& at(std::size_t row, std::size_t col) const;

    Matrix sub(std::size_t row_begin, std::size_t row_end) const;

    Vector get_row(std::size_t row) const;
    Vector operator[](std::size_t row) const;

    Matrix copy() const;

    Matrix transpose() const;

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& operator/=(const Matrix& m);
    Matrix& operator+=(num_t x);
    Matrix& operator-=(num_t x);
    Matrix& operator*=(num_t x);
    Matrix& operator/=(num_t x);

    static Matrix with(std::size_t rows, std::size_t cols, num_t val);
    static Matrix zeros(std::size_t rows, std::size_t cols);
    static Matrix ones(std::size_t rows, std::size_t cols);
    static Matrix id(std::size_t n);
    static Matrix ref(RealChunk* chunk, num_t* ptr, std::size_t rows, std::size_t cols);

    static Matrix hstack(const std::vector<Matrix>& mats);

private:
    RealChunk* chunk_;
    num_t* ptr_;
    std::size_t rows_;
    std::size_t cols_;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);
SerialWriter& operator<<(SerialWriter& os, const Matrix& m);
SerialReader& operator>>(SerialReader& is, Matrix& m);

Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, const Matrix& b);
Matrix operator/(const Matrix& a, const Matrix& b);
Matrix operator+(const Matrix& a, num_t b);
Matrix operator-(const Matrix& a, num_t b);
Matrix operator*(const Matrix& a, num_t b);
Matrix operator/(const Matrix& a, num_t b);
Matrix operator+(num_t a, const Matrix& b);
Matrix operator-(num_t a, const Matrix& b);
Matrix operator*(num_t a, const Matrix& b);
Matrix operator/(num_t a, const Matrix& b);
Matrix operator-(const Matrix& a);

bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);

Matrix sgn(const Matrix& v);
Matrix abs(const Matrix& v);
Matrix pow(const Matrix& v, num_t x);
Matrix sqrt(const Matrix& v);
Matrix exp(const Matrix& v);
Matrix log(const Matrix& v);
Matrix cos(const Matrix& v);
Matrix sin(const Matrix& v);
Matrix tan(const Matrix& v);
Matrix acos(const Matrix& v);
Matrix asin(const Matrix& v);
Matrix atan(const Matrix& v);
Matrix cosh(const Matrix& v);
Matrix sinh(const Matrix& v);
Matrix tanh(const Matrix& v);
Matrix acosh(const Matrix& v);
Matrix asinh(const Matrix& v);
Matrix atanh(const Matrix& v);
num_t min(const Matrix& v);
num_t max(const Matrix& v);
num_t min_abs(const Matrix& v);
num_t max_abs(const Matrix& v);
num_t sum(const Matrix& v);
num_t product(const Matrix& v);
num_t mean(const Matrix& v);

Matrix sigmoid(const Matrix& v);
Matrix sigmoid_prime(const Matrix& v);
Matrix softmax(const Matrix& m);

num_t norm(const Matrix& a);
num_t norm_square(const Matrix& a);
num_t dist(const Matrix& a, const Matrix& b);
num_t dist_square(const Matrix& a, const Matrix& b);
Matrix dot(const Matrix& a, const Matrix& b);
Vector dot(const Matrix& a, const Vector& b);
Vector dot(const Vector& a, const Matrix& b);
Matrix outer_product(const Vector& a, const Vector& b);

bool fequals(const Matrix& a, const Matrix& b);
bool fzero(const Matrix& m);


Matrix outer(const Vector& a, const Vector& b);


#include "matrix.hxx"
