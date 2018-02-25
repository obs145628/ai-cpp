#include "datasets/mnist.hh"
#include <cassert>
#include <iostream>
#include "la/random.hh"

namespace norm4
{


    void load(Matrix& x_train, Matrix& y_train,
	      Matrix& x_test, Matrix& y_test,
	      std::size_t train_len, std::size_t test_len)
    {

	x_train = Matrix(train_len, 4);
	y_train = Matrix(train_len, 2);
	x_test = Matrix(test_len, 4);
	y_test = Matrix(test_len, 2);

	std::fill(y_train.begin(), y_train.end(), 0);
	std::fill(y_test.begin(), y_test.end(), 0);

	for (std::size_t i = 0; i < train_len + test_len; ++i)
	{
	    Vector xi = i < train_len ? x_train[i] : x_test[i - train_len];
	    Vector yi = i < train_len ? y_train[i] : y_test[i - train_len];

	    nrandom::fill_double(xi.begin(), xi.end());
	    yi[static_cast<int>((norm(xi)))] = 1.0;
	}


    }

    Vector value_to_vector(int x)
    {
	assert(x == 0 || x == 1);
	Vector res = Vector::zeros(2);
	res[x] = 1;
	return res;
    }

    int vector_to_value(const Vector& v)
    {
	assert(v.size() == 2);
	return argmax(v);
    }
    
    bool output_test(const Vector& a, const Vector& b)
    {
	return vector_to_value(a) == vector_to_value(b);
    }
    
}
