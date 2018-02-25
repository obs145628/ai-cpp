#pragma once

#include "layer.hh"
#include "activation.hh"


class FullyConnectedLayer : public Layer
{

public:

    FullyConnectedLayer(std::size_t input_size,
			std::size_t output_size,
			Activation* activ);
    virtual ~FullyConnectedLayer();


    std::size_t input_size() const override;
    std::size_t output_size() const override;
    Vector forward(const Vector& v) override;
    Vector backpropagation(const Vector& da) override;
    void update_params(num_t lr, num_t lambda1, num_t lambda2) override;
    num_t check_grad(Network& net, const Matrix& x, const Matrix& y) override;

    void numerical_propagation(Network& net, const Matrix& x, const Matrix& y,
			       Matrix& dw, Vector& db);

    template <class Fn>
    void init_weigths(Fn init);
    

private:
    std::size_t input_size_;
    std::size_t output_size_;
    Activation* activ_;
    Matrix w_;
    Vector b_;
    Vector x_;
    Vector z_;
    Vector a_;
    Matrix cumul_dw_;
    Vector cumul_db_;
};


#include "fully-connected-layer.hxx"
