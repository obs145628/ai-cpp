#pragma once

#include "fwd.hh"


class Optimizer
{
public:
    virtual ~Optimizer() = default;

    virtual void run(Network& net, const Matrix& x, const Matrix& y) = 0;
};
