#include "dnn/sgd-optimizer.hh"
#include "dnn/layer.hh"
#include "dnn/network.hh"

SGDOptimizer::SGDOptimizer(num_t lr, std::size_t batch_size, num_t lambda1, num_t lambda2)
    : lr_(lr)
    , batch_size_(batch_size)
    , lambda1_(lambda1)
    , lambda2_(lambda2)
{}

void SGDOptimizer::run(Network& net, const Matrix& x, const Matrix& y)
{
    assert(x.rows() == y.rows());
    std::size_t n = x.rows();
    //shuffle arrays

    for (std::size_t k = 0; k < n; k += batch_size_)
    {
	std::size_t m = std::min(n - k, batch_size_);
	for (std::size_t i = 0; i < m; ++i)
	    net.backpropagation(x[k + i], y[k + i]);
	for (auto& l : net.layers_get())
	    l->update_params(lr_ / m, lr_ * lambda1_ / n, lr_ * lambda2_ / n);
    }

    //for (std::size_t l = 0; l < layers_.size(); ++l)
//	debug_add(layers_[l]->w, layers_[l]->b);
}
