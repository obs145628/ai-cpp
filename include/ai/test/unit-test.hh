#pragma once

#include <string>
#include <vector>
#include "test-register.hh"


#define TEST(EX) check_(static_cast<bool>(EX), __FILE__, #EX, __LINE__)
#define TEST_EQ(E1, E2) check_eq_((E1), (E2), __FILE__, #E1, #E2, __LINE__)

template <class T>
class UnitTest : public TestRegister
{
public:

    using test_f = void (T::*)();


    void run() override;

    int success_get() const override;
    int total_get() const override;

protected:
    void register_test(const std::string& name, test_f fn);


    void begin_test_();
    void end_test_();
    void check_(bool valid, const char* file, const char* ex, int line);

    template <class U>
    void check_eq_(const U& v1, const U& v2, const char* file,
		   const char* e1, const char* e2, int line);

private:
    std::vector<test_f> tests_methods_;
    std::vector<std::string> tests_names_;
    std::size_t curr_test_;
    std::size_t max_names_size_;
    int sucess_;
    int total_;

    int ut_success_;
    int ut_total_;

};

#include "unit-test.hxx"
