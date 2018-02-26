#include <fstream>
#include "fwd.hh"
#include "../la/tensor.hh"

#pragma once

void debug_add();
template<class T, class... Tail>
void debug_add(T head, Tail... tail);

std::vector<Tensor> debug_load(const char* path);

#include "debug-tensors.hxx"
