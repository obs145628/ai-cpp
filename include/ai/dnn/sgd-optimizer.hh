#pragma once

#include "optimizer.hh"

class SGDOptimizer : public Optimizer
{
public:

    /**
     * @param lr - learning rate
     * @param batch_size - size of a mini batch
     * @param lambda1 - coefficient for L1 regularization
     * @param lambda2 - coefficient for L2 regularization
     */
    SGDOptimizer(num_t lr, std::size_t batch_size, num_t lambda1 = 0, num_t lambda2 = 0);

    /**
     *
     * @param net - neural network to be optimized
     * @param X - matrix n * p containing training input
     * @param y - matrix n * q contraining training expected results
     *
     * stochastic Gradient Descent:
     * Shuffle data
     * Divide data in mini_batches of len batch_size,
     *apply stochastic gradient descent on each of them
     *
     *for each mini batch:
     *  for each training example x run backpropagation
     *  for each layer update params using learning rate, l1 regularization and l2 regularization
     */
    void run(Network& net, const Matrix& x, const Matrix& y) override;

private:
    num_t lr_;
    std::size_t batch_size_;
    num_t lambda1_;
    num_t lambda2_;
};
