#include "test/test-suite.hh"
#include "la-types-test.hh"
#include "tests-test.hh"

int main()
{
    auto& test_suite = TestSuite::Instance();
    test_suite.summary_os_set(std::cout);
    test_suite.details_os_set(std::cout);

    TestsTest t1;
    LATypesTest t2;

    test_suite.add("test_suite", &t1);
    test_suite.add("la_types", &t2);

    test_suite.init();
    test_suite.run();
    return 0;
}
