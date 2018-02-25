#include "dnn/activation.hh"

const char* SigmoidActivation::name() const
{
    return "sigmoid";
}

void SigmoidActivation::compute(const num_t* in_begin, const num_t* in_end,
				num_t* out_begin)
{
    vect_sigmoid(in_begin, in_end, out_begin);
}

void SigmoidActivation::compute_prime(const num_t* in_begin, const num_t* in_end,
				      num_t* out_begin)
{
    vect_sigmoid_prime(in_begin, in_end, out_begin);
}
