#pragma once

#include "../la/matrix.hh"

namespace norm4
{

    void load(Matrix& x_train, Matrix& y_train,
	      Matrix& x_test, Matrix& y_test,
	      std::size_t train_len, std::size_t test_len);

    /**
     * Convert a value (0/1) to a vector of size 2
     * v[i] = 1(x == i)
     */
    Vector value_to_vector(int x);

    /**
     * Convert a vector of size 2 to a value (0/1)
     * digit = argmax(v)
     */
    int vector_to_value(const Vector& v);

    /**
     * Check if two vectors correponds to she same value
     */
    bool output_test(const Vector& a, const Vector& b);
    
}
