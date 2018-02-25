#pragma once

#include "debug-tensors.hh"
#include "fully-connected-layer.hh"

template <class Fn>
void FullyConnectedLayer::init_weigths(Fn init)
{
    init(w_.begin(), w_.end());
    init(b_.begin(), b_.end());
    //debug_add(w_, b_);
}
