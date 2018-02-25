#pragma once

#include <cstddef>
#include <iostream>
#include "real-chunk.hh"
#include "shape.hh"
#include "io/serial.hh"


class Vector
{
public:
    Vector();
    explicit Vector(std::size_t size);
    explicit Vector(const std::initializer_list<num_t>& vals);

    template <class It>
    Vector(It begin, It end);

    Vector(const Vector& v);
    Vector(Vector&& v);
    ~Vector();

    Vector& operator=(const Vector& v);
    Vector& operator=(Vector&& v);

    void assign(std::size_t size);
    void assign(const Vector& v);
    void assign(const std::initializer_list<num_t>& vals);

    num_t* begin();
    const num_t* begin() const;
    num_t* end();
    const num_t* end() const;
    num_t& at(std::size_t i);
    const num_t& at(std::size_t i) const;
    num_t& operator[](std::size_t i);
    const num_t& operator[](std::size_t i) const;
    std::size_t size() const;
    Shape shape() const;
    RealChunk* chunk() const;

    Vector copy() const;
    Vector sub(std::size_t begin, std::size_t end) const;


    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(const Vector& v);
    Vector& operator/=(const Vector& v);
    Vector& operator+=(num_t x);
    Vector& operator-=(num_t x);
    Vector& operator*=(num_t x);
    Vector& operator/=(num_t x);

    static Vector with(std::size_t n, num_t val);
    static Vector zeros(std::size_t n);
    static Vector ones(std::size_t n);
    static Vector ref(RealChunk* chunk, num_t* ptr, std::size_t size);

private:
    RealChunk* chunk_;
    num_t* ptr_;
    std::size_t size_;
};

std::ostream& operator<<(std::ostream& os, const Vector& v);
SerialWriter& operator<<(SerialWriter& os, const Vector& v);
SerialReader& operator>>(SerialReader& is, Vector& v);

Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);
Vector operator*(const Vector& a, const Vector& b);
Vector operator/(const Vector& a, const Vector& b);
Vector operator+(const Vector& a, num_t b);
Vector operator-(const Vector& a, num_t b);
Vector operator*(const Vector& a, num_t b);
Vector operator/(const Vector& a, num_t b);
Vector operator+(num_t a, const Vector& b);
Vector operator-(num_t a, const Vector& b);
Vector operator*(num_t a, const Vector& b);
Vector operator/(num_t a, const Vector& b);
bool  operator==(const Vector& a, const Vector& b);
bool  operator!=(const Vector& a, const Vector& b);

num_t norm(const Vector& v);
num_t norm_square(const Vector& v);
Vector normalize(const Vector& v);
num_t dot(const Vector& a, const Vector& b);
num_t dist_square(const Vector& a, const Vector& b);
num_t dist(const Vector& a, const Vector& b);

Vector sgn(const Vector& v);
Vector abs(const Vector& v);
Vector pow(const Vector& v, num_t x);
Vector sqrt(const Vector& v);
Vector exp(const Vector& v);
Vector log(const Vector& v);
Vector cos(const Vector& v);
Vector sin(const Vector& v);
Vector tan(const Vector& v);
Vector acos(const Vector& v);
Vector asin(const Vector& v);
Vector atan(const Vector& v);
Vector cosh(const Vector& v);
Vector sinh(const Vector& v);
Vector tanh(const Vector& v);
Vector acosh(const Vector& v);
Vector asinh(const Vector& v);
Vector atanh(const Vector& v);
num_t min(const Vector& v);
num_t max(const Vector& v);
num_t min_abs(const Vector& v);
num_t max_abs(const Vector& v);
num_t sum(const Vector& v);
num_t product(const Vector& v);
num_t mean(const Vector& v);

Vector sigmoid(const Vector& v);
Vector sigmoid_prime(const Vector& v);
Vector softmax(const Vector& v);

bool fequals(const Vector& a, const Vector& b);
bool fzero(const Vector& v);

std::size_t argmax(const Vector& v);

#include "vector.hxx"
