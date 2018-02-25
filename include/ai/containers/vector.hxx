#include "vector.hh"
#include <algorithm>
#include <cassert>

#define MIN_RESERVE 32

template <class T>
Vector<T>::Vector(std::size_t size)
    : size_(size)
    , reserve_(reserve_len_(size))
    , data_(new T[reserve_])
{}

template <class T>
Vector<T>::Vector(const Vector<T>& v)
    : Vector(v.data_, v.data_ + v.size_)
{}

template <class T>
Vector<T>::Vector(Vector&& v) noexcept
    : size_(v.size_)
    , reserve_(v.reserve_)
    , data_(v.data_)
{
    v.data_ = nullptr;
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T>& l)
    : Vector(l.begin(), l.end())
{}

template <class T>
template <class It>
Vector<T>::Vector(It begin, It end)
    : Vector(std::distance(begin, end))
{
    std::copy(begin, end, data_);
}

template <class T>
Vector<T>::~Vector()
{
    delete[] data_;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& v)
{
    assign(v.data_, v.data_ + v.size_);
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& v) noexcept
{
    size_ = v.size_;
    reserve_ = v.reserve_;
    data_ = v.data_;
    v.data_ = nullptr;
}

template <class T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& l)
{
    assign(l.begin(), l.end());
    return *this;
}

template <class T>
template <class It>
void Vector<T>::assign(It begin, It end)
{
    std::size_t size = std::distance(begin, end);
    if (size > reserve_)
    {
	reserve_ = reserve_len_(size);
	T* new_data = new T[reserve_];
	delete data_;
	data_ = new_data;
    }

    size_ = size;
    std::copy(begin, end, data_);
}

template <class T>
bool Vector<T>::empty() const
{
    return !size_;
}

template <class T>
std::size_t Vector<T>::size() const
{
    return size_;
}

template <class T>
T* Vector<T>::data() noexcept
{
    return data_;
}

template <class T>
const T* Vector<T>::data() const noexcept
{
    return data_;
}

template <class T>
T& Vector<T>::operator[](std::size_t i)
{
    assert(i < size_);
    return data_[i];
}

template <class T>
const T& Vector<T>::operator[](std::size_t i) const
{
    assert(i < size_);
    return data_[i];
}



template <class T>
std::size_t Vector<T>::reserve_len_(std::size_t size)
{
    std::size_t res = MIN_RESERVE;
    while (res < size)
	res *= 2;
    return res;
}

template <class T>
void Vector<T>::resize_(std::size_t new_size, std::size_t new_reserve)
{
    double* new_data = new double[new_reserve];
    std::copy(data_, data_ + new_size, new_data);
    delete[] data_;

    size_ = new_size;
    reserve_ = new_reserve;
    data_ = new_data;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v)
{
    os << '{';

    if (!v.empty())
    {
	os << v[0];
	for (std::size_t i = 1; i < v.size(); ++i)
	    os << ", " << v[i];
    }
    
    return os << '}';
}


#undef MIN_RESERVE
