#pragma once

#include <vector>
#include "../la/matrix.hh"
#include "../la/vector.hh"

class Activation;
class Layer;
class Network;
class Optimizer;


using vector_list_t = std::vector<Vector>;
using matrix_list_t = std::vector<Matrix>;

using layers_t = std::vector<Layer*>;
