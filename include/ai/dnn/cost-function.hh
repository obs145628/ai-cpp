#pragma once

#include "fwd.hh"

class CostFunction
{

public:

    virtual ~CostFunction() = default;

    virtual const char* name() const = 0;

    /**
     * Compute the error value for one inut vector
     * @param y (output_size) - expected output vector
     * @param y_hat (output_size) - output vector of the network
     * @return cost error value
     */
    virtual num_t cost(const Vector& y, const Vector& y_hat) const = 0;

    /**
     * Compute the cost error derivative at output layer (dC/da)
     * @param y (output_size) - expected output vector
     * @param y_hat (output_size, 1) - output vector of the network
     * @return (output_size) - vector dC/da
     */
    virtual Vector cost_prime(const Vector& y, const Vector& y_hat) const = 0;
    
};

class QuadraticCost : public CostFunction
{
public:
    const char* name() const override;
    num_t cost(const Vector& y, const Vector& y_hat) const override;
    Vector cost_prime(const Vector& y, const Vector& y_hat) const override;
};

class CrossEntropyCost : public CostFunction
{
public:
    const char* name() const override;
    num_t cost(const Vector& y, const Vector& y_hat) const override;
    Vector cost_prime(const Vector& y, const Vector& y_hat) const override;
};

#include "cost-function.hxx"
