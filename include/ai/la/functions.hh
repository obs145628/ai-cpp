#pragma once

#include <cmath>
#include "fwd.hh"

static constexpr num_t EPSILON = 1e-10;

num_t sigmoid(num_t z);
num_t sigmoid_prime(num_t z);
num_t dot(num_t a, num_t b);
num_t sgn(num_t a);
num_t relu(num_t z);
num_t relu_prime(num_t z);
num_t tanh_prime(num_t z);

bool fequals(num_t a, num_t b);
bool fzero(num_t x);

template <class In1, class In2, class Out>
void vect_add(In1 begin1, In1 end1, In2 begin2, Out begin3);
template <class In1, class In2, class Out>
void vect_sub(In1 begin1, In1 end1, In2 begin2, Out begin3);
template <class In1, class In2, class Out>
void vect_mul(In1 begin1, In1 end1, In2 begin2, Out begin3);
template <class In1, class In2, class Out>
void vect_div(In1 begin1, In1 end1, In2 begin2, Out begin3);
template <class In1, class In2, class Out>
void vect_mod(In1 begin1, In1 end1, In2 begin2, Out begin3);
template <class In, class Out>
void vect_neg(In begin1, In end1, Out begin2);
template <class In, class T, class Out>
void vect_num_add(In begin1, In end1, const T& val, Out begin2);
template <class In, class T, class Out>
void vect_num_add(In begin1, In end1, const T& val, Out begin2);
template <class In, class T, class Out>
void vect_num_sub(In begin1, In end1, const T& val, Out begin2);
template <class In, class T, class Out>
void vect_num_mul(In begin1, In end1, const T& val, Out begin2);
template <class In, class T, class Out>
void vect_num_div(In begin1, In end1, const T& val, Out begin2);
template <class T, class In, class Out>
void num_vect_add(const T& val, In begin1, In end1, Out begin2);
template <class T, class In, class Out>
void num_vect_sub(const T& val, In begin1, In end1, Out begin2);
template <class T, class In, class Out>
void num_vect_mul(const T& val, In begin1, In end1, Out begin2);
template <class T, class In, class Out>
void num_vect_div(const T& val, In begin1, In end1, Out begin2);
template <class In1, class In2>
bool vect_equals(In1 begin1, In1 end1, In2 begin2);

template <class In>
auto vect_norm(In begin, In end);
template <class In>
auto vect_norm_square(In begin, In end);
template <class In1, class In2>
auto vect_dot(In1 begin1, In1 end1, In2 begin2);
template <class In1, class In2>
auto vect_dist_square(In1 begin1, In1 end1, In2 begin2);
template <class In1, class In2>
auto vect_dist(In1 begin1, In1 end1, In2 begin2);
template <class In, class Out>
void vect_abs(In begin1, In end1, Out begin2);
template <class In, class Out, class T>
void vect_pow(In begin1, In end1, const T& val, Out begin2);
template <class In, class Out>
void vect_sqrt(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_exp(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_log(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_cos(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_sin(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_tan(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_acos(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_asin(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_atan(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_cosh(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_sinh(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_tanh(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_acosh(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_asinh(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_atanh(In begin1, In end1, Out begin2);
template <class In>
auto vect_min(In begin, In end);
template <class In>
auto vect_max(In begin, In end);
template <class In>
auto vect_min_abs(In begin, In end);
template <class In>
auto vect_max_abs(In begin, In end);
template <class In>
auto vect_sum(In begin, In end);
template <class In>
auto vect_product(In begin, In end);
template <class In>
auto vect_mean(In begin, In end);

template <class In, class Out>
void vect_sigmoid(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_sigmoid_prime(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_relu(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_relu_prime(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_tanh_prime(In begin1, In end1, Out begin2);
template <class In, class Out>
void vect_sgn(In begin1, In end1, Out begin2);
template <class In1, class In2>
bool vect_fequals(In1 begin1, In1 end1, In2 begin2);
template <class In>
bool vect_fzero(In begin, In end);



template <class In1, class In2, class Out>
void vect_outer(In1 begin1, In1 end1, In2 begin2, In2 end2, Out begin3);



#include "functions.hxx"


