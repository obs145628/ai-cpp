#pragma once

#include "tensor.hh"

inline Tensor::Tensor()
    : shape_()
    , chunk_(nullptr)
    , ptr_(nullptr)
{}

inline Tensor::Tensor(const Shape& shape)
    : shape_(shape)
    , chunk_(RealChunk::alloc(shape_.size()))
    , ptr_(chunk_->data)
{
    chunk_->ref();
}

inline Tensor::Tensor(const Vector& v)
    : shape_(v.shape())
    , chunk_(v.chunk())
    , ptr_(const_cast<num_t*>(v.begin()))
{
    if (chunk_)
	chunk_->ref();
}

inline Tensor::Tensor(const Matrix& m)
    : shape_(m.shape())
    , chunk_(m.chunk())
    , ptr_(const_cast<num_t*>(m.begin()))
{
    if (chunk_)
	chunk_->ref();
}

template <class It>
inline Tensor::Tensor(const Shape& shape,
	       It begin_data, It end_data)
    : Tensor(shape)
{
    std::copy(begin_data, end_data, this->begin());
}

inline Tensor::Tensor(const Tensor& t)
    : shape_(t.shape_)
    , chunk_(t.chunk_)
    , ptr_(t.ptr_)
{
    if (chunk_)
	chunk_->ref();
}

inline Tensor::Tensor(Tensor&& t)
    : shape_(t.shape_)
    , chunk_(t.chunk_)
    , ptr_(t.ptr_)
{
    t.chunk_ = nullptr;
}


inline Tensor::~Tensor()
{
    if (chunk_)
    {
	chunk_->unref();
    }
}

inline Tensor& Tensor::operator=(const Tensor& t)
{
    if (&t == this)
        return *this;
    if (chunk_)
        chunk_->unref();

    shape_ = t.shape_;
    chunk_ = t.chunk_;
    ptr_ = t.ptr_;

    if (chunk_)
        chunk_->ref();
    return *this;
}

inline Tensor& Tensor::operator=(Tensor&& t)
{
    if (&t == this)
        return *this;
    if (chunk_)
        chunk_->unref();

    shape_ = t.shape_;
    chunk_ = t.chunk_;
    ptr_ = t.ptr_;

    t.chunk_ = nullptr;
    return *this;
}

inline Tensor& Tensor::operator=(const Shape& s)
{
    if (chunk_)
        chunk_->unref();

    shape_ = s;
    chunk_ = RealChunk::alloc(s.size());
    ptr_ = chunk_->data;
    chunk_->ref();

    return *this;
}

inline num_t* Tensor::begin()
{
    return ptr_;
}

inline const num_t* Tensor::begin() const
{
    return ptr_;
}

inline num_t* Tensor::end()
{
    return ptr_ + shape_.size();
}

inline const num_t* Tensor::end() const
{
    return ptr_ + shape_.size();
}

inline const Shape& Tensor::shape() const
{
    return shape_;
}

inline std::size_t Tensor::size() const
{
    return shape_.size();
}

inline std::size_t Tensor::ndims() const
{
    return shape_.size();
}

inline std::size_t Tensor::dim_get(std::size_t i) const
{
    return shape_.dim_get(i);
}

inline RealChunk* Tensor::chunk() const
{
    return chunk_;
}

inline Tensor Tensor::get_sub(std::size_t i) const
{
    //FIXME
    (void) i;
    return *this;
}

inline Tensor Tensor::operator[](std::size_t i) const
{
    return get_sub(i);
}


inline Tensor Tensor::copy() const
{
    return Tensor(shape_, begin(), end());
}

inline Tensor Tensor::ref(RealChunk* chunk, num_t* ptr, const Shape& shape)
{
    assert(ptr >= chunk->data);
    assert(ptr + shape.size() <= chunk->data + chunk->size);
    Tensor t;
    t.chunk_ = chunk;
    t.ptr_ = ptr;
    t.shape_ = shape;
    chunk->ref();
    return t;
}

inline Tensor& Tensor::operator+=(const Tensor& t)
{
    assert(size() == t.size());
    vect_add(begin(), end(), t.begin(), begin());
    return *this;
}

inline Tensor& Tensor::operator-=(const Tensor& t)
{
    assert(size() == t.size());
    vect_sub(begin(), end(), t.begin(), begin());
    return *this;
}

inline Tensor& Tensor::operator*=(const Tensor& t)
{
    assert(size() == t.size());
    vect_mul(begin(), end(), t.begin(), begin());
    return *this;
}

inline Tensor& Tensor::operator/=(const Tensor& t)
{
    assert(size() == t.size());
    vect_div(begin(), end(), t.begin(), begin());
    return *this;
}

inline Tensor& Tensor::operator+=(num_t x)
{
    vect_num_add(begin(), end(), x, begin());
    return *this;
}

inline Tensor& Tensor::operator-=(num_t x)
{
    vect_num_sub(begin(), end(), x, begin());
    return *this;
}

inline Tensor& Tensor::operator*=(num_t x)
{
    vect_num_mul(begin(), end(), x, begin());
    return *this;
}

inline Tensor& Tensor::operator/=(num_t x)
{
    vect_num_div(begin(), end(), x, begin());
    return *this;
}

inline Tensor operator+(const Tensor& a, const Tensor& b)
{
    assert(a.size() == b.size());
    Tensor res(a.shape());
    vect_add(a.begin(), a.end(), b.begin(), res.begin()); 
    return res;
}

inline Tensor operator-(const Tensor& a, const Tensor& b)
{
    assert(a.size() == b.size());
    Tensor res(a.shape());
    vect_sub(a.begin(), a.end(), b.begin(), res.begin()); 
    return res;
}

inline Tensor operator*(const Tensor& a, const Tensor& b)
{
    assert(a.size() == b.size());
    Tensor res(a.shape());
    vect_mul(a.begin(), a.end(), b.begin(), res.begin()); 
    return res;
}

inline Tensor operator/(const Tensor& a, const Tensor& b)
{
    assert(a.size() == b.size());
    Tensor res(a.shape());
    vect_div(a.begin(), a.end(), b.begin(), res.begin()); 
    return res;
}

inline Tensor operator+(const Tensor& a, num_t b)
{
    Tensor res(a.shape());
    vect_num_add(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Tensor operator-(const Tensor& a, num_t b)
{
    Tensor res(a.shape());
    vect_num_sub(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Tensor operator*(const Tensor& a, num_t b)
{
    Tensor res(a.shape());
    vect_num_mul(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Tensor operator/(const Tensor& a, num_t b)
{
    Tensor res(a.shape());
    vect_num_div(a.begin(), a.end(), b, res.begin());
    return res;
}

inline Tensor operator+(num_t a, const Tensor& b)
{
    Tensor res(b.shape());
    num_vect_add(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Tensor operator-(num_t a, const Tensor& b)
{
    Tensor res(b.shape());
    num_vect_sub(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Tensor operator*(num_t a, const Tensor& b)
{
    Tensor res(b.shape());
    num_vect_mul(a, b.begin(), b.end(), res.begin());
    return res;
}

inline Tensor operator/(num_t a, const Tensor& b)
{
    Tensor res(b.shape());
    num_vect_div(a, b.begin(), b.end(), res.begin());
    return res;
}


inline bool operator==(const Tensor& a, const Tensor& b)
{
    return a.shape() == b.shape() && vect_equals(a.begin(), a.end(), b.begin());
}

inline bool operator!=(const Tensor& a, const Tensor& b)
{
    return !(a == b);
}

inline num_t norm(const Tensor& t)
{
    return vect_norm(t.begin(), t.end());
}

inline num_t norm_square(const Tensor& t)
{
    return vect_norm_square(t.begin(), t.end());
}

inline num_t dist_square(const Tensor& a, const Tensor& b)
{
    assert(a.shape() == b.shape());
    return vect_dist_square(a.begin(), a.end(), b.begin());
}

inline num_t dist(const Tensor& a, const Tensor& b)
{
    assert(a.size() == b.size());
    return vect_dist(a.begin(), a.end(), b.begin());
}

inline Tensor sgn(const Tensor& v)
{
    Tensor res(v.shape());
    vect_sgn(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor abs(const Tensor& v)
{
    Tensor res(v.shape());
    vect_abs(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor pow(const Tensor& v, num_t x)
{
    Tensor res(v.shape());
    vect_pow(v.begin(), v.end(), x, res.begin());
    return res;
}

inline Tensor sqrt(const Tensor& v)
{
    Tensor res(v.shape());
    vect_sqrt(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor exp(const Tensor& v)
{
    Tensor res(v.shape());
    vect_exp(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor log(const Tensor& v)
{
    Tensor res(v.shape());
    vect_sgn(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor cos(const Tensor& v)
{
    Tensor res(v.shape());
    vect_cos(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor sin(const Tensor& v)
{
    Tensor res(v.shape());
    vect_sin(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor tan(const Tensor& v)
{
    Tensor res(v.shape());
    vect_tan(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor acos(const Tensor& v)
{
    Tensor res(v.shape());
    vect_acos(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor asin(const Tensor& v)
{
    Tensor res(v.shape());
    vect_asin(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor atan(const Tensor& v)
{
    Tensor res(v.shape());
    vect_atan(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor cosh(const Tensor& v)
{
    Tensor res(v.shape());
    vect_cosh(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor sinh(const Tensor& v)
{
    Tensor res(v.shape());
    vect_sinh(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor tanh(const Tensor& v)
{
    Tensor res(v.shape());
    vect_tanh(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor acosh(const Tensor& v)
{
    Tensor res(v.shape());
    vect_acosh(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor asinh(const Tensor& v)
{
    Tensor res(v.shape());
    vect_asinh(v.begin(), v.end(), res.begin());
    return res;
}

inline Tensor atanh(const Tensor& v)
{
    Tensor res(v.shape());
    vect_atanh(v.begin(), v.end(), res.begin());
    return res;
}

inline num_t min(const Tensor& t)
{
    return vect_min(t.begin(), t.end());
}

inline num_t max(const Tensor& t)
{
    return vect_max(t.begin(), t.end());
}

inline num_t min_abs(const Tensor& t)
{
    return vect_min_abs(t.begin(), t.end());
}

inline num_t max_abs(const Tensor& t)
{
    return vect_max_abs(t.begin(), t.end());
}

inline num_t sum(const Tensor& t)
{
    return vect_sum(t.begin(), t.end());
}

inline num_t product(const Tensor& t)
{
    return vect_product(t.begin(), t.end());
}

inline num_t mean(const Tensor& t)
{
    return vect_mean(t.begin(), t.end());
}

inline Tensor sigmoid(const Tensor& t)    
{
    Tensor res(t.shape());
    vect_sigmoid(t.begin(), t.end(), res.begin());
    return res;
}

inline Tensor sigmoid_prime(const Tensor& t)
{
    Tensor res(t.shape());
    vect_sigmoid_prime(t.begin(), t.end(), res.begin());
    return res;
}
