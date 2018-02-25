#include "dnn/fully-connected-layer.hh"
#include <iostream>
#include "dnn/activation.hh"
#include "dnn/network.hh"

namespace
{
    constexpr num_t EGRAD = 1e-8;
}

FullyConnectedLayer::FullyConnectedLayer(std::size_t input_size,
					 std::size_t output_size,
					 Activation* activ)
    : input_size_(input_size)
    , output_size_(output_size)
    , activ_(activ)
    , w_(output_size_, input_size_)
    , b_(output_size_)
    , x_(input_size_)
    , z_(output_size_)
    , a_(output_size_)
    , cumul_dw_(Matrix::zeros(output_size_, input_size_))
    , cumul_db_(Vector::zeros(output_size_))
{}

FullyConnectedLayer::~FullyConnectedLayer()
{
    delete activ_;
}

std::size_t FullyConnectedLayer::input_size() const
{
    return input_size_;
}

std::size_t FullyConnectedLayer::output_size() const
{
    return output_size_;
}

Vector FullyConnectedLayer::forward(const Vector& v)
{
    x_ = v;
    z_ = dot(w_, x_) + b_;
    activ_->compute(z_.begin(), z_.end(), a_.begin());
    return a_;
}


Vector FullyConnectedLayer::backpropagation(const Vector& da)
{
    Vector act_prime(output_size_);
    activ_->compute_prime(z_.begin(), z_.end(), act_prime.begin());
    Vector dz = da * act_prime;
    Matrix dw = outer(dz, x_);
    Vector db = dz;
    Vector dx = dot(w_.transpose(), dz);

    cumul_dw_ += dw;
    cumul_db_ += db;
    
    return dx;
}

void FullyConnectedLayer::update_params(num_t lr, num_t lambda1, num_t lambda2)
{
    Matrix new_w = w_ - lr * cumul_dw_;
    Vector new_b = b_ - lr * cumul_db_;

    if (lambda1 != 0)
	new_w -= lambda1 * sgn(w_);
    if (lambda2 != 0)
	new_w -= lambda2 * w_;

    w_ = new_w;
    b_ = new_b;

    std::fill(cumul_dw_.begin(), cumul_dw_.end(), 0);
    std::fill(cumul_db_.begin(), cumul_db_.end(), 0);
}

num_t FullyConnectedLayer::check_grad(Network& net, const Matrix& x, const Matrix& y)
{
    Matrix num_dw;
    Vector num_db;
    numerical_propagation(net, x, y, num_dw, num_db);
    
    num_t diff_dw = dist(num_dw, cumul_dw_);
    num_t diff_db = dist(num_db, cumul_db_);

    std::cout << "dw dist: " << diff_dw << std::endl;
    std::cout << "db dist: " << diff_db << std::endl;

    return std::max(diff_dw, diff_db);
}

void FullyConnectedLayer::numerical_propagation(Network& net, const Matrix& x, const Matrix& y,
						Matrix& dw, Vector& db)
{
    dw = Matrix(output_size_, input_size_);
    db = Vector(output_size_);

    for (std::size_t i = 0; i < output_size_; ++i)
	for (std::size_t j = 0; j < input_size_; ++j)
	{
	    num_t old_val = w_(i, j);
	    w_(i, j) = old_val + EGRAD;
	    num_t cost_xp = net.data_cost(x, y);
	    w_(i, j) = old_val - EGRAD;
	    num_t cost_xn = net.data_cost(x, y);
	    dw(i, j) = (cost_xp - cost_xn) / (2 * EGRAD);
	    w_(i, j) = old_val;
	}

    for (std::size_t i = 0; i < output_size_; ++i)
    {
	num_t old_val = b_[i];
	b_[i] = old_val + EGRAD;
	num_t cost_xp = net.data_cost(x, y);
	b_[i] = old_val - EGRAD;
	num_t cost_xn = net.data_cost(x, y);
	db[i] = (cost_xp - cost_xn) / (2 * EGRAD);
	b_[i] = old_val;
    }

    dw *= x.rows();
    db *= x.rows();
}
