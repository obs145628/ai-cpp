#pragma once

#include <array>
#include <initializer_list>
#include <iostream>
#include <vector>

class Shape
{
public:
    static constexpr std::size_t MAX_DIM = 8;

    Shape();
    Shape(const Shape& shape);
    explicit Shape(const std::vector<std::size_t>& dims);
    explicit Shape(const std::initializer_list<std::size_t>& dims);

    Shape& operator=(const Shape& shape);

    std::size_t size() const;
    std::size_t ndims() const;
    std::size_t dim_get(std::size_t i) const;
    
private:
    std::size_t size_;
    std::size_t len_;
    std::size_t dims_[MAX_DIM];
};

std::ostream& operator<<(std::ostream& os, const Shape& shape);

bool operator==(const Shape& a, const Shape& b);
bool operator!=(const Shape& a, const Shape& b);

#include "shape.hxx"
