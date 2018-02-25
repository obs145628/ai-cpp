#pragma once

#include <cstddef>
#include <iostream>
#include "fwd.hh"
#include "matrix.hh"
#include "real-chunk.hh"
#include "shape.hh"
#include "vector.hh"

class Tensor
{
public:

    Tensor();
    Tensor(const Shape& shape);
    Tensor(const Vector& v);
    Tensor(const Matrix& m);

    template <class It>
    Tensor(const Shape& shape,
	   It begin_data, It end_data);

    Tensor(const Tensor& t);
    Tensor(Tensor&& t);
    ~Tensor();

    Tensor& operator=(const Tensor& t);
    Tensor& operator=(Tensor&& t);
    Tensor& operator=(const Shape& s);

    num_t* begin();
    const num_t* begin() const;
    num_t* end();
    const num_t* end() const;

    const Shape& shape() const;
    std::size_t size() const;
    std::size_t ndims() const;
    std::size_t dim_get(std::size_t i) const;
    RealChunk* chunk() const;

    Tensor get_sub(std::size_t i) const;
    Tensor operator[](std::size_t i) const;

    Tensor copy() const;

    static Tensor ref(RealChunk* chunk, num_t* ptr, const Shape& shape);

    Tensor& operator+=(const Tensor& t);
    Tensor& operator-=(const Tensor& t);
    Tensor& operator*=(const Tensor& t);
    Tensor& operator/=(const Tensor& t);
    Tensor& operator+=(num_t x);
    Tensor& operator-=(num_t x);
    Tensor& operator*=(num_t x);
    Tensor& operator/=(num_t x);

private:
    Shape shape_;
    RealChunk* chunk_;
    num_t* ptr_;
};

SerialWriter& operator<<(SerialWriter& os, const Tensor& t);
SerialReader& operator>>(SerialReader& is, Tensor& t);

Tensor operator+(const Tensor& a, const Tensor& b);
Tensor operator-(const Tensor& a, const Tensor& b);
Tensor operator*(const Tensor& a, const Tensor& b);
Tensor operator/(const Tensor& a, const Tensor& b);
Tensor operator+(const Tensor& a, num_t b);
Tensor operator-(const Tensor& a, num_t b);
Tensor operator*(const Tensor& a, num_t b);
Tensor operator/(const Tensor& a, num_t b);
Tensor operator+(num_t a, const Tensor& b);
Tensor operator-(num_t a, const Tensor& b);
Tensor operator*(num_t a, const Tensor& b);
Tensor operator/(num_t a, const Tensor& b);

bool operator==(const Tensor& a, const Tensor& b);
bool operator!=(const Tensor& a, const Tensor& b);

num_t norm(const Tensor& t);
num_t norm_square(const Tensor& t);
num_t dist_square(const Tensor& a, const Tensor& b);
num_t dist(const Tensor& a, const Tensor& b);

Tensor sgn(const Tensor& t);
Tensor abs(const Tensor& t);
Tensor pow(const Tensor& t, num_t x);
Tensor sqrt(const Tensor& t);
Tensor exp(const Tensor& t);
Tensor log(const Tensor& t);
Tensor cos(const Tensor& t);
Tensor sin(const Tensor& t);
Tensor tan(const Tensor& t);
Tensor acos(const Tensor& t);
Tensor asin(const Tensor& t);
Tensor atan(const Tensor& t);
Tensor cosh(const Tensor& t);
Tensor sinh(const Tensor& t);
Tensor tanh(const Tensor& t);
Tensor acosh(const Tensor& t);
Tensor asinh(const Tensor& t);
Tensor atanh(const Tensor& t);
num_t min(const Tensor& t);
num_t max(const Tensor& t);
num_t min_abs(const Tensor& t);
num_t max_abs(const Tensor& t);
num_t sum(const Tensor& t);
num_t product(const Tensor& t);
num_t mean(const Tensor& t);

Tensor sigmoid(const Tensor& v);
Tensor sigmoid_prime(const Tensor& v);

#include "tensor.hxx"
