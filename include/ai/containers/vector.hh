#pragma once

#include <cstddef>
#include <initializer_list>
#include <ostream>

template <class T>
class Vector
{
public:
    Vector(std::size_t size = 0);
    Vector(const Vector& v);
    Vector(Vector&& v) noexcept;
    Vector(const std::initializer_list<T>& l);

    template <class It>
    Vector(It begin, It end);
    
    ~Vector();

    Vector& operator=(const Vector& v);
    Vector& operator=(Vector&& v) noexcept;
    Vector& operator=(const std::initializer_list<T>& l);

    template <class It>
    void assign(It begin, It end);

    bool empty() const;
    std::size_t size() const;

    T* data() noexcept;
    const T* data() const noexcept;

    T& operator[](std::size_t i);
    const T& operator[](std::size_t i) const;

private:
    std::size_t size_;
    std::size_t reserve_;
    T* data_;

    static std::size_t reserve_len_(std::size_t size);
    void resize_(std::size_t new_size, std::size_t new_reserve);
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v);

#include "vector.hxx"
