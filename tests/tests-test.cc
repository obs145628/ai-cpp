#include "tests-test.hh"

void TestsTest::init()
{
  register_test("general", &TestsTest::test_general);
}

void TestsTest::test_general()
{
    TEST(1 == 1);
    TEST(1 != 0);
}
