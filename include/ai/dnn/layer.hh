#pragma once

#include "fwd.hh"


class Layer
{

public:

    virtual ~Layer() = default;

    virtual std::size_t input_size() const = 0;
    virtual std::size_t output_size() const = 0;

    /**
     * Apply forward propgation on vector v
     * @param v (input_size) - input vector
     * @return vector (output_size)
     */
    virtual Vector forward(const Vector& v) = 0;

    /**
     * Backpropagation
     * @param da (output_size) - vector of gradients dC/da
     * @return vector(input_size)

     * apply backward propagation to compute dC/d??? for each parameters of the layer
     * called for each training set, compute from the last call to forward
     * Cumulate dC/d??? until the call to update wieghts
     * return vector of gradients dC/dx
     */
    virtual Vector backpropagation(const Vector& da) = 0;

    /**
     * Update the parameters of the layer
     * @param lr - learning rate
     * @param lambda1 - coefficient for l1 regularization
     * @param lambda2 - coefficient for l2 regularization
     * Update the parameters of the layers according to the cumulated DC/d??? 
     * from previous calls to backpropagation
     */
    virtual void update_params(num_t lr, num_t lambda1, num_t lambda2) = 0;

    /**
     * Check the backpropagation algorithm with numerical computations
     * @param net - neural network
     * @param x - full training set examples
     * @param y - full training set labels
     * @return difference between backpropagation and numerical computation
     * Assume backpropagation was already called on the whole dataset
     */
    virtual num_t check_grad(Network& net, const Matrix& x, const Matrix& y) = 0;
    
};
