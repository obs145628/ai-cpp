#pragma once

#include "test/unit-test.hh"

class LATypesTest : public UnitTest<LATypesTest>
{

public:

    void init() override;


    void test_vector_ops();
    void test_vector_functions();
    void test_dot();
    void test_serial();

};
