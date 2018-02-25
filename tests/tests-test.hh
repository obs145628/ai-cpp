#pragma  once

#include "test/unit-test.hh"

class TestsTest : public UnitTest<TestsTest>
{

public:

    void init() override;

    void test_general();

};

