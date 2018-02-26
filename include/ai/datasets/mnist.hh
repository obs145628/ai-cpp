#pragma once

#include "../la/matrix.hh"

namespace mnist
{

    constexpr int DATASET_LEN = 70000;
    constexpr int IMG_LEN = 28 * 28;

    /**
     * Load random samples of train data and test data from the MNIST dataset
     */
    void load(Matrix& x_train, Matrix& y_train,
	      Matrix& x_test, Matrix& y_test,
	      std::size_t train_len, std::size_t test_len);

    /**
     * Load random samples of train data and test data from the MNIST dataset
     * Only load 0 and 1 numbers
     */
    void load_bin(Matrix& x_train, Vector& y_train,
		  Matrix& x_test, Vector& y_test,
		  std::size_t train_len, std::size_t test_len);

    /**
     * Convert a digit from 0 to 9 to a vector of size 10
     * v[i] = 1(digit == i)
     */
    Vector digit_to_vector(std::size_t digit);

    /**
     * Convert a vector of size 10 to a digit from 0 to 9
     * digit = argmax(v)
     */
    std::size_t vector_to_digit(const Vector& v);

    /**
     * Check if two vectors correponds to she same digit
     */
    bool output_test(const Vector& a, const Vector& b);
    
}
