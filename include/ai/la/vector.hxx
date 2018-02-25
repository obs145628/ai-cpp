#pragma once

#include <cassert>
#include "functions.hxx"


inline Vector::Vector()
        : chunk_(nullptr)
        , ptr_(nullptr)
        , size_(0)
{}

inline Vector::Vector(std::size_t size)
        : chunk_(RealChunk::alloc(size))
        , ptr_(chunk_->data)
        , size_(size)
{
    chunk_->ref();
}

inline Vector::Vector(const std::initializer_list<num_t>& vals)
        : Vector(vals.begin(), vals.end())
{}

template <class It>
inline Vector::Vector(It begin, It end)
        : Vector(end - begin)
{
    std::copy(begin, end, this->begin());
}

inline Vector::Vector(const Vector &v)
        : chunk_(v.chunk_)
        , ptr_(v.ptr_)
        , size_(v.size_)
{
    if (chunk_)
        chunk_->ref();
}

inline Vector::Vector(Vector&& v)
        : chunk_(v.chunk_)
        , ptr_(v.ptr_)
        , size_(v.size_)
{
    v.chunk_ = nullptr;
}

inline Vector::~Vector()
{
    if (chunk_)
    {
        chunk_->unref();
    }
}

inline Vector& Vector::operator=(const Vector& v)
{
    assign(v);
    return *this;
}

inline Vector& Vector::operator=(Vector&& v)
{
    if (&v == this)
        return *this;

    if (chunk_)
        chunk_->unref();

    chunk_ = v.chunk_;
    ptr_ = v.ptr_;
    size_ = v.size_;
    v.chunk_ = nullptr;
    return *this;
}

inline void Vector::assign(std::size_t size)
{
    if (chunk_)
        chunk_->unref();

    chunk_ = RealChunk::alloc(size);
    chunk_->ref();
    ptr_ = chunk_->data;
    size_ = size;
}

inline void Vector::assign(const Vector& v)
{
    if (&v == this)
        return;

    chunk_ = v.chunk_;
    ptr_ = v.ptr_;
    size_ = v.size_;
    if (chunk_)
        chunk_->ref();
}

inline void Vector::assign(const std::initializer_list<num_t>& vals)
{
    if (chunk_)
        chunk_->unref();

    chunk_ = RealChunk::alloc(vals.size());
    chunk_->ref();
    ptr_ = chunk_->data;
    size_ = vals.size();
    std::copy(vals.begin(), vals.end(), begin());
}

inline num_t* Vector::begin()
{
    return ptr_;
}

inline const num_t* Vector::begin() const
{
    return ptr_;
}

inline num_t* Vector::end()
{
    return ptr_ + size_;
}

inline const num_t* Vector::end() const
{
    return ptr_ + size_;
}

inline num_t& Vector::at(std::size_t i)
{
    assert(i < size_);
    return ptr_[i];
}

inline const num_t& Vector::at(std::size_t i) const
{
    assert(i < size_);
    return ptr_[i];
}

inline num_t& Vector::operator[](std::size_t i)
{
    return at(i);
}

inline const num_t& Vector::operator[](std::size_t i) const
{
    return at(i);
}

inline std::size_t Vector::size() const
{
    return size_;
}

inline Shape Vector::shape() const
{
    return Shape({size_});
}

inline RealChunk* Vector::chunk() const
{
    return chunk_;
}

inline Vector Vector::copy() const
{
    return Vector(begin(), end());
}

inline Vector Vector::sub(std::size_t begin, std::size_t end) const
{
    assert(begin < size());
    assert(end <= size());
    assert(begin < end);
    return Vector::ref(chunk_, ptr_ + begin, end - begin);
}





inline Vector& Vector::operator+=(const Vector& v)
{
    assert(size_ == v.size_);
    vect_add(ptr_, ptr_ + size_, v.ptr_, ptr_);
    return *this;
}

inline Vector& Vector::operator-=(const Vector& v)
{
    assert(size_ == v.size_);
    vect_sub(ptr_, ptr_ + size_, v.ptr_, ptr_);
    return *this;
}

inline Vector& Vector::operator*=(const Vector& v)
{
    assert(size_ == v.size_);
    vect_mul(ptr_, ptr_ + size_, v.ptr_, ptr_);
    return *this;
}

inline Vector& Vector::operator/=(const Vector& v)
{
    assert(size_ == v.size_);
    vect_div(ptr_, ptr_ + size_, v.ptr_, ptr_);
    return *this;
}

inline Vector& Vector::operator+=(num_t x)
{
    vect_num_add(ptr_, ptr_ + size_, x, ptr_);
    return *this;
}

inline Vector& Vector::operator-=(num_t x)
{
    vect_num_sub(ptr_, ptr_ + size_, x, ptr_);
    return *this;
}

inline Vector& Vector::operator*=(num_t x)
{
    vect_num_mul(ptr_, ptr_ + size_, x, ptr_);
    return *this;
}

inline Vector& Vector::operator/=(num_t x)
{
    vect_num_div(ptr_, ptr_ + size_, x, ptr_);
    return *this;
}

inline Vector operator+(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    Vector res(a.size());
    vect_add(a.begin(), a.end(), b.begin(), res.begin()); 
    return res;
}

inline Vector operator-(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    Vector res(a.size());
    vect_sub(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Vector operator*(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    Vector res(a.size());
    vect_mul(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Vector operator/(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    Vector res(a.size());
    vect_div(a.begin(), a.end(), b.begin(), res.begin());
    return res;
}

inline Vector operator+(const Vector& a, num_t b)
{
    Vector res(a.size());
    vect_num_add(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Vector operator-(const Vector& a, num_t b)
{
    Vector res(a.size());
    vect_num_sub(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Vector operator*(const Vector& a, num_t b)
{
    Vector res(a.size());
    vect_num_mul(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Vector operator/(const Vector& a, num_t b)
{
    Vector res(a.size());
    vect_num_div(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Vector operator+(num_t a, const Vector& b)
{
    Vector res(b.size());
    num_vect_add(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Vector operator-(num_t a, const Vector& b)
{
    Vector res(b.size());
    num_vect_sub(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Vector operator*(num_t a, const Vector& b)
{
    Vector res(b.size());
    num_vect_mul(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Vector operator/(num_t a, const Vector& b)
{
    Vector res(b.size());
    num_vect_div(a, b.begin(), b.end(), res.begin());
    return res;
}

inline bool operator==(const Vector& a, const Vector& b)
{
    return a.size() == b.size() && vect_equals(a.begin(), a.end(), b.begin());
}

inline bool operator!=(const Vector& a, const Vector& b)
{
    return !(a == b);
}

inline num_t norm(const Vector& v)
{
    return vect_norm(v.begin(), v.end());
}

inline num_t norm_square(const Vector& v)
{
    return vect_norm_square(v.begin(), v.end());
}

inline Vector normalize(const Vector& v)
{
    return v / norm(v);
}

inline num_t dot(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    return vect_dot(a.begin(), a.end(), b.begin());
}

inline num_t dist_square(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    return vect_dist_square(a.begin(), a.end(), b.begin());
}

inline num_t dist(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    return vect_dist(a.begin(), a.end(), b.begin());
}

inline Vector sgn(const Vector& v)
{
    Vector res(v.size());
    vect_sgn(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector abs(const Vector& v)
{
    Vector res(v.size());
    vect_abs(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector pow(const Vector& v, num_t x)
{
    Vector res(v.size());
    vect_pow(v.begin(), v.end(), x, res.begin());
    return res;
}

inline Vector sqrt(const Vector& v)
{
    Vector res(v.size());
    vect_sqrt(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector exp(const Vector& v)
{
    Vector res(v.size());
    vect_exp(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector log(const Vector& v)
{
    Vector res(v.size());
    vect_log(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector cos(const Vector& v)
{
    Vector res(v.size());
    vect_cos(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector sin(const Vector& v)
{
    Vector res(v.size());
    vect_sin(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector tan(const Vector& v)
{
    Vector res(v.size());
    vect_tan(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector acos(const Vector& v)
{
    Vector res(v.size());
    vect_acos(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector asin(const Vector& v)
{
    Vector res(v.size());
    vect_asin(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector atan(const Vector& v)
{
    Vector res(v.size());
    vect_atan(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector cosh(const Vector& v)
{
    Vector res(v.size());
    vect_cosh(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector sinh(const Vector& v)
{
    Vector res(v.size());
    vect_sinh(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector tanh(const Vector& v)
{
    Vector res(v.size());
    vect_tanh(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector acosh(const Vector& v)
{
    Vector res(v.size());
    vect_acosh(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector asinh(const Vector& v)
{
    Vector res(v.size());
    vect_asinh(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector atanh(const Vector& v)
{
    Vector res(v.size());
    vect_atanh(v.begin(), v.end(), res.begin());
    return res;
}

inline num_t min(const Vector& v)
{
    return vect_min(v.begin(), v.end());
}

inline num_t max(const Vector& v)
{
    return vect_max(v.begin(), v.end());
}

inline num_t min_abs(const Vector& v)
{
    return vect_min_abs(v.begin(), v.end());
}

inline num_t max_abs(const Vector& v)
{
    return vect_max_abs(v.begin(), v.end());
}

inline num_t sum(const Vector& v)
{
    return vect_sum(v.begin(), v.end());
}

inline num_t product(const Vector& v)
{
    return vect_product(v.begin(), v.end());
}

inline num_t mean(const Vector& v)
{
    return vect_mean(v.begin(), v.end());
}





inline Vector Vector::with(std::size_t n, num_t val)
{
    Vector v(n);
    std::fill(v.begin(), v.end(), val);
    return v;
}

inline Vector Vector::zeros(std::size_t n)
{
    return with(n, 0);
}

inline Vector Vector::ones(std::size_t n)
{
    return with(n, 1);
}

inline Vector Vector::ref(RealChunk* chunk, num_t* ptr, std::size_t size)
{
    assert(ptr >= chunk->data);
    assert(ptr + size <= chunk->data + chunk->size);
    Vector v;
    v.chunk_ = chunk;
    v.ptr_ = ptr;
    v.size_ = size;
    chunk->ref();
    return v;
}


inline Vector sigmoid(const Vector& v)
{
    Vector res(v.size());
    vect_sigmoid(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector sigmoid_prime(const Vector& v)
{
    Vector res(v.size());
    vect_sigmoid_prime(v.begin(), v.end(), res.begin());
    return res;
}

inline Vector softmax(const Vector& v)
{
    num_t m = max(v);
    Vector res = exp(v - m);
    return res / sum(res);
}


inline bool fequals(const Vector& a, const Vector& b)
{
    assert(a.size() == b.size());
    return vect_fequals(a.begin(), a.end(), b.begin());
}

inline bool fzero(const Vector& v)
{
    return vect_fzero(v.begin(), v.end());
}


inline std::size_t argmax(const Vector& v)
{
    std::size_t res = 0;
    for (std::size_t i = 1; i < v.size(); ++i)
	if (v[i] > v[res])
	    res = i;
    return res;
}
