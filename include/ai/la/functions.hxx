#pragma once

#include "functions.hh"
#include <type_traits>

inline num_t sigmoid(num_t z)
{
    return 1.0 / (1.0 + std::exp(-z));
}

inline num_t sigmoid_prime(num_t z)
{
    return std::exp(-z) /  ((1.0 + std::exp(-z)) * (1.0 + std::exp(-z)));
}

inline num_t relu(num_t z)
{
    return std::max(num_t(0), z);
}

inline num_t relu_prime(num_t z)
{
    return z > 0;
}

inline num_t tanh_prime(num_t z)
{
    return 1.0 - std::tanh(z) * std::tanh(z);
}


inline num_t dot(num_t a, num_t b)
{
    return a * b;
}

inline num_t sgn(num_t a)
{
    return a < 0. ? -1. : a > 0.;
}

inline bool fequals(num_t a, num_t b)
{
    return (a - b) * (a - b) < EPSILON;
}

inline bool fzero(num_t x)
{
    return x * x < EPSILON;
}






template <class In1, class In2, class Out>
void vect_add(In1 begin1, In1 end1, In2 begin2, Out begin3)
{
    auto i1 = begin1;
    auto i2 = begin2;
    auto i3 = begin3;
    while (i1 != end1)
	*(i3++) = *(i1++) + *(i2++); 
}

template <class In1, class In2, class Out>
void vect_sub(In1 begin1, In1 end1, In2 begin2, Out begin3)
{
    auto i1 = begin1;
    auto i2 = begin2;
    auto i3 = begin3;
    while (i1 != end1)
	*(i3++) = *(i1++) - *(i2++);     
}

template <class In1, class In2, class Out>
void vect_mul(In1 begin1, In1 end1, In2 begin2, Out begin3)
{
    auto i1 = begin1;
    auto i2 = begin2;
    auto i3 = begin3;
    while (i1 != end1)
	*(i3++) = *(i1++) * *(i2++); 
}

template <class In1, class In2, class Out>
void vect_div(In1 begin1, In1 end1, In2 begin2, Out begin3)
{
    auto i1 = begin1;
    auto i2 = begin2;
    auto i3 = begin3;
    while (i1 != end1)
	*(i3++) = *(i1++) / *(i2++); 
}

template <class In1, class In2, class Out>
void vect_mod(In1 begin1, In1 end1, In2 begin2, Out begin3)
{
    auto i1 = begin1;
    auto i2 = begin2;
    auto i3 = begin3;
    while (i1 != end1)
	*(i3++) = *(i1++) % *(i2++); 
}

template <class In, class Out>
void vect_neg(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = -*(i1++);
}

template <class In, class T, class Out>
void vect_num_add(In begin1, In end1, const T& val, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = *(i1++) + val;
}

template <class In, class T, class Out>
void vect_num_sub(In begin1, In end1, const T& val, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = *(i1++) - val;
}

template <class In, class T, class Out>
void vect_num_mul(In begin1, In end1, const T& val, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = *(i1++) * val;
}

template <class In, class T, class Out>
void vect_num_div(In begin1, In end1, const T& val, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = *(i1++) / val;
}

template <class T, class In, class Out>
void num_vect_add(const T& val, In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = val + *(i1++);
}

template <class T, class In, class Out>
void num_vect_sub(const T& val, In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = val - *(i1++);
}

template <class T, class In, class Out>
void num_vect_mul(const T& val, In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = val * *(i1++);
}

template <class T, class In, class Out>
void num_vect_div(const T& val, In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = val / *(i1++);
}

template <class In1, class In2>
bool vect_equals(In1 begin1, In1 end1, In2 begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	if (*(i1++) != *(i2++))
	    return false;
    return true;
}

template <class In>
auto vect_norm(In begin, In end)
{
    return std::sqrt(vect_norm_square(begin, end));
}

template <class In>
auto vect_norm_square(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {0};
    while (begin != end)
    {
	res += *begin * *begin;
        ++begin;
    }
    return res;
}

template <class In1, class In2>
auto vect_dot(In1 begin1, In1 end1, In2 begin2)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin1)>>;
    val_t res {0};
    auto it1 = begin1;
    auto it2 = begin2;
    
    while (it1 != end1)
	res += *(it1++) * *(it2++);
    return res;
}

template <class In1, class In2>
auto vect_dist_square(In1 begin1, In1 end1, In2 begin2)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin1)>>;
    val_t res {0};
    auto it1 = begin1;
    auto it2 = begin2;
    
    while (it1 != end1)
    {
	res += (*it1 - *it2) * (*it1 - *it2);
	++it1;
	++it2;
    }
    return res;
}

template <class In1, class In2>
auto vect_dist(In1 begin1, In1 end1, In2 begin2)
{
    return std::sqrt(vect_dist_square(begin1, end1, begin2));
}

template <class In, class Out>
void vect_abs(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::fabs(*(i1++));
}

template <class In, class Out, class T>
void vect_pow(In begin1, In end1, const T& val, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::pow(*(i1++), val);
}

template <class In, class Out>
void vect_sqrt(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::sqrt(*(i1++));
}

template <class In, class Out>
void vect_exp(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::exp(*(i1++));
}


template <class In, class Out>
void vect_log(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::log(*(i1++));
}

template <class In, class Out>
void vect_cos(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::cos(*(i1++));
}


template <class In, class Out>
void vect_sin(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::sin(*(i1++));
}

template <class In, class Out>
void vect_tan(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::tan(*(i1++));
}

template <class In, class Out>
void vect_acos(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::acos(*(i1++));
}

template <class In, class Out>
void vect_asin(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::asin(*(i1++));
}

template <class In, class Out>
void vect_atan(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::atan(*(i1++));
}

template <class In, class Out>
void vect_cosh(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::cosh(*(i1++));
}

template <class In, class Out>
void vect_sinh(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::sinh(*(i1++));
}

template <class In, class Out>
void vect_tanh(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::tanh(*(i1++));
}

template <class In, class Out>
void vect_acosh(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::acosh(*(i1++));
}

template <class In, class Out>
void vect_asinh(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::asinh(*(i1++));
}

template <class In, class Out>
void vect_atanh(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = std::atanh(*(i1++));
}

template <class In>
auto vect_min(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {1e20};
    while (begin != end)
	res = std::min(res, *(begin++));
    return res;
}

template <class In>
auto vect_max(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {-1e20};
    while (begin != end)
	res = std::max(res, *(begin++));
    return res;
}

template <class In>
auto vect_min_abs(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {1e20};
    while (begin != end)
	res = std::min(res, std::abs(*(begin++)));
    return res;
}

template <class In>
auto vect_max_abs(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {-1e20};
    while (begin != end)
	res = std::max(res, std::abs(*(begin++)));
    return res;
}

template <class In>
auto vect_sum(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {0};
    while (begin != end)
	res += *(begin++);
    return res;
}

template <class In>
auto vect_product(In begin, In end)
{
    using val_t = std::remove_const_t<std::remove_reference_t<decltype(*begin)>>;
    val_t res {1};
    while (begin != end)
	res *= *(begin++);
    return res;
}

template <class In>
auto vect_mean(In begin, In end)
{
    return vect_sum(begin, end) / std::distance(begin, end);
}


template <class In, class Out>
void vect_sigmoid(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = sigmoid(*(i1++));
}

template <class In, class Out>
void vect_sigmoid_prime(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = sigmoid_prime(*(i1++));
}

template <class In, class Out>
void vect_relu(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = relu(*(i1++));
}

template <class In, class Out>
void vect_relu_prime(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = relu_prime(*(i1++));
}

template <class In, class Out>
void vect_tanh_prime(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = tanh_prime(*(i1++));
}


template <class In, class Out>
void vect_sgn(In begin1, In end1, Out begin2)
{
    auto i1 = begin1;
    auto i2 = begin2;
    while (i1 != end1)
	*(i2++) = sgn(*(i1++));
}

template <class In1, class In2>
bool vect_fequals(In1 begin1, In1 end1, In2 begin2)
{
    return vect_dist_square(begin1, end1, begin2) < EPSILON;
}

template <class In>
bool vect_fzero(In begin, In end)
{
    return vect_norm_square(begin, end) < EPSILON;
}

template <class In1, class In2, class Out>
void vect_outer(In1 begin1, In1 end1, In2 begin2, In2 end2, Out begin3)
{
    std::size_t m = std::distance(begin1, end1);
    std::size_t n = std::distance(begin2, end2);

    for (std::size_t i = 0; i < m; ++i)
	for (std::size_t j = 0; j < n; ++j)
	    begin3[i * n + j] = begin1[i] * begin2[j];
	    
}
