#include "dnn/network.hh"
#include "dnn/layer.hh"
#include "la/tensor_ops.hh"
#include "dnn/activation.hh"
#include "dnn/debug-tensors.hh"
#include "dnn/optimizer.hh"

namespace
{
    constexpr num_t ERR_BACKPROP = 1e-2;
}

Network::Network(const layers_t& layers, CostFunction* cost,
		 test_f test_function)
    : layers_(layers)
    , cost_(cost)
    , test_function_(test_function)
{}

Network::~Network()
{
    for (auto l : layers_)
	delete l;
    delete cost_;
}

layers_t& Network::layers_get()
{
    return layers_;
}

const layers_t& Network::layers_get() const
{
    return layers_;
}


Vector Network::forward(Vector x)
{
    for (auto l : layers_)
	x = l->forward(x);
    return x;
}

void Network::backpropagation(const Vector& x, const Vector& y)
{
    Vector y_hat = forward(x);
    Vector da = cost_->cost_prime(y, y_hat);
    for (auto it = layers_.rbegin(); it != layers_.rend(); ++it)
	da = (*it)->backpropagation(da);
}

num_t Network::data_cost(const Matrix& x, const Matrix& y)
{
    std::size_t n = x.rows();
    num_t res = 0;

    for (std::size_t i = 0; i < n; ++i)
    {
	Vector y_hat = forward(x[i]);
	res += cost_->cost(y[i], y_hat);
    }

    res /= num_t(n);
    return res;
}


void Network::evaluate(const Matrix& x, const Matrix& y)
{
    std::size_t n = x.rows();
    std::size_t valid = 0;

    for (std::size_t i = 0; i < n; ++i)
	valid += test_function_(forward(x[i]), y[i]);
    
    double acc = (valid * 100.0) / n;
    std::cout << "Evalutation: " << valid << "/" << n << " (" << acc << "%)\n";
}

void Network::train(Matrix& x_train, Matrix& y_train, Matrix& x_test, Matrix& y_test,
		    Optimizer& opti, std::size_t epochs,
		    bool disp_train_cost)
{
    for (std::size_t i = 1; i <= epochs; ++i)
    {
	std::cout << "Epoch: " << i << ": " << std::endl;
	opti.run(*this, x_train, y_train);
	evaluate(x_test, y_test);

	if (disp_train_cost)
	    std::cout << "Train cost: " << data_cost(x_train, y_train) << std::endl;
    }
}


bool Network::check_backpropagation(const Matrix& x, const Matrix& y)
{
    bool valid = true;
    for (std::size_t i = 0; i < x.rows(); ++i)
	backpropagation(x[i], y[i]);

    for (std::size_t i = 0; i < layers_.size(); ++i)
    {
	std::cout << "Layer " << (i + 1) << ": " << std::endl;
	num_t val = layers_[i]->check_grad(*this, x, y);
	bool succ = val < ERR_BACKPROP;
	if (!succ)
	{
	    std::cout << "Invalid layer" << std::endl;
	    valid = false;
	}
    }

    return valid;
}
