#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "test-register.hh"

class TestSuite
{
public:

    static TestSuite& Instance();

    TestSuite(const TestSuite&) = delete;
    TestSuite(TestSuite&&) = delete;
    TestSuite& operator=(const TestSuite&) = delete;
    TestSuite& operator=(TestSuite&&) = delete;


    void add(const std::string& name, TestRegister* test);

    void init();
    void run();

    void summary_os_set(std::ostream& os);
    void details_os_set(std::ostream& os);

    std::ostream& summary_os_get();
    std::ostream& details_os_get();

private:

    void begin_test_();
    void end_test_();

    std::ostream* summary_os_;
    std::ostream* details_os_;

    std::vector<std::string> tests_names_;
    std::vector<TestRegister*> tests_objects_;
    std::size_t current_test_;
    int ts_success_;
    int ts_total_;

    TestSuite() = default;
};
