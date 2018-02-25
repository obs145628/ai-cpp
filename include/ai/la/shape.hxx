#pragma once

#include "shape.hh"
#include <cassert>

template <class It>
std::size_t shape_size(It begin, It end)
{
    std::size_t res = 1;
    for (It it = begin; it != end; ++it)
	res *= *it;
    return res;
}

inline Shape::Shape()
    : size_(0)
    , len_(0)
{}

inline Shape::Shape(const std::vector<std::size_t>& dims)
    : size_(shape_size(dims.begin(), dims.end()))
    , len_(dims.size())
{
    assert(len_ < MAX_DIM);
    std::copy(dims.begin(), dims.end(), dims_);
}

inline Shape::Shape(const std::initializer_list<std::size_t>& dims)
    : size_(shape_size(dims.begin(), dims.end()))
    , len_(dims.size())
{
    assert(len_ < MAX_DIM);
    std::copy(dims.begin(), dims.end(), dims_);
}

inline Shape::Shape(const Shape& shape)
    : size_(shape.size_)
    , len_(shape.len_)
{
    std::copy(shape.dims_, shape.dims_ + len_, dims_);
}

inline Shape& Shape::operator=(const Shape& shape)
{
    size_ = shape.size_;
    len_ = shape.len_;
    std::copy(shape.dims_, shape.dims_ + len_, dims_);
    return *this;
}

inline std::size_t Shape::size() const
{
    return size_;
}

inline std::size_t Shape::ndims() const
{
    return len_;
}

inline std::size_t Shape::dim_get(std::size_t i) const
{
    return dims_[i];
}


inline std::ostream& operator<<(std::ostream& os, const Shape& shape)
{
    os << '(';
    for (std::size_t i = 0; i < shape.ndims(); ++i)
    {
	os << shape.dim_get(i);
	if (i + 1 != shape.ndims())
	    os << ", ";
    }
    os << ')';
    return os;
}


inline bool operator==(const Shape& a, const Shape& b)
{
    if (a.ndims() != b.ndims() || a.size() != b.size())
	return false;

    for (std::size_t i = 0; i < a.ndims(); ++i)
	if (a.dim_get(i) != b.dim_get(i))
	    return false;

    return true;
}

inline bool operator!=(const Shape& a, const Shape& b)
{
    return !(a == b); 
}
