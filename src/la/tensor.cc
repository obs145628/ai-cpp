#include "la/tensor.hh"

SerialWriter& operator<<(SerialWriter& os, const Tensor& t)
{
    os << t.shape().ndims();
    for (std::size_t i = 0; i < t.shape().ndims(); ++i)
	os << t.shape().dim_get(i);
    os.write(t.begin(), t.end());
    return os;
}

SerialReader& operator>>(SerialReader& is, Tensor& t)
{
    std::size_t ndims;
    is >> ndims;

    std::vector<std::size_t> dims(ndims);
    for (auto& val : dims)
	is >> val;
    

    t = Shape(dims);
    is.read(t.begin(), t.end());
    return is;
}
