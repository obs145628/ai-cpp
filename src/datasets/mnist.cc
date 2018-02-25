#include "datasets/mnist.hh"
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "la/random.hh"

namespace mnist
{

    namespace
    {
	const char* PATH = "mnist.data";
    }

    void load(Matrix& x_train, Matrix& y_train,
	      Matrix& x_test, Matrix& y_test,
	      std::size_t train_len, std::size_t test_len)
    {
	std::size_t total_len = train_len + test_len;
	assert(total_len <= DATASET_LEN);

	std::ifstream is(PATH);
	if (!is.is_open())
	    throw std::runtime_error("can't open mnist data file");
	
	x_train = Matrix(train_len, IMG_LEN);
	y_train = Matrix(train_len, 10);
	x_test = Matrix(test_len, IMG_LEN);
	y_test = Matrix(test_len, 10);
	std::fill(y_train.begin(), y_train.end(), 0);
	std::fill(y_test.begin(), y_test.end(), 0);

	
	std::vector<std::size_t> indexs(total_len);
	for (std::size_t i = 0; i < total_len; ++i)
	    indexs[i] = i;
	nrandom::shuffle(indexs.begin(), indexs.end());

	for (std::size_t j = 0; j < total_len; ++j)
	{
	    std::size_t i = indexs[j];
	    Vector x_row = i < train_len ? x_train[i] : x_test[i - train_len];
	    Vector y_row = i < train_len ? y_train[i] : y_test[i - train_len];
	    unsigned char pixs[IMG_LEN];
	    char digit;

	    is.read(reinterpret_cast<char*>(pixs), IMG_LEN);
	    is.read(&digit, 1);

	    for (std::size_t i = 0; i < IMG_LEN; ++i)
		x_row[i] = pixs[i] / 255.0;
	    y_row[digit] = 1.0;
	}
	
    }

    void load_bin(Matrix& x_train, Vector& y_train,
		  Matrix& x_test, Vector& y_test,
		  std::size_t train_len, std::size_t test_len)
    {
	std::size_t total_len = train_len + test_len;
	assert(total_len <= DATASET_LEN);

	std::ifstream is(PATH);
	if (!is.is_open())
	    throw std::runtime_error("can't open mnist data file");
	
	x_train = Matrix(train_len, IMG_LEN);
	y_train = Vector(train_len);
	x_test = Matrix(test_len, IMG_LEN);
	y_test = Vector(test_len);
	std::fill(y_train.begin(), y_train.end(), 0);
	std::fill(y_test.begin(), y_test.end(), 0);

	
	std::vector<std::size_t> indexs(total_len);
	for (std::size_t i = 0; i < total_len; ++i)
	    indexs[i] = i;
	nrandom::shuffle(indexs.begin(), indexs.end());

	std::size_t j = 0;
	while (j < total_len)
	{
	    std::size_t i = indexs[j];

	    if (is.eof())
		throw std::runtime_error("mnist: unexpected end of file");
	    
	    Vector x_row = i < train_len ? x_train[i] : x_test[i - train_len];
	    num_t& y_row = i < train_len ? y_train[i] : y_test[i - train_len];
	    unsigned char pixs[IMG_LEN];
	    char digit;

	    is.read(reinterpret_cast<char*>(pixs), IMG_LEN);
	    is.read(&digit, 1);

	    if (digit != 0 && digit != 1)
		continue;

	    for (std::size_t i = 0; i < IMG_LEN; ++i)
		x_row[i] = pixs[i] / 255.0;
	    y_row = digit;
	    ++j;
	}
	
    }

    Vector digit_to_vector(std::size_t digit)
    {
	assert(digit < 10);
	Vector res = Vector::zeros(10);
	res[digit] = 1;
	return res;
    }

    std::size_t vector_to_digit(const Vector& v)
    {
	assert(v.size() == 10);
	return argmax(v);
    }
    
    bool output_test(const Vector& a, const Vector& b)
    {
	return vector_to_digit(a) == vector_to_digit(b);
    }
    
}
