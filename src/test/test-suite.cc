#include "test/test-suite.hh"

TestSuite& TestSuite::Instance()
{
    static TestSuite instance;
    return instance;
}


void TestSuite::add(const std::string& name, TestRegister* test)
{
    tests_names_.push_back(name);
    tests_objects_.push_back(test);
}

void TestSuite::summary_os_set(std::ostream& os)
{
    summary_os_ = &os;
}

void TestSuite::details_os_set(std::ostream& os)
{
    details_os_ = &os;
}

void TestSuite::init()
{
    for (std::size_t i = 0; i < tests_objects_.size(); ++i)
    {
        tests_objects_[i]->init();
    }
}

void TestSuite::run()
{
    ts_success_ = 0;
    ts_total_ = 0;

    for (current_test_ = 0; current_test_ < tests_objects_.size(); ++current_test_)
    {
        begin_test_();
        tests_objects_[current_test_]->run();
        end_test_();
    }

    double acc = ts_total_ == 0 ? 1 : ts_success_ / double(ts_total_);
    double per = acc * 100.0;
    per = int(per * 1000) / 1000.0;

    *summary_os_ << "Global Results: "
                 << ": " << ts_success_ << " / " << ts_total_
                 << " (" << per << "%)\n";
}

void TestSuite::begin_test_()
{
    *summary_os_ << "Running testsuite " << tests_names_[current_test_] << "\n";
}

void TestSuite::end_test_()
{
    int total = tests_objects_[current_test_]->total_get();
    int success = tests_objects_[current_test_]->success_get();

    double acc = total == 0 ? 1 : success / double(total);
    double per = acc * 100.0;
    per = int(per * 1000) / 1000.0;

    *summary_os_ << "Test suite " << tests_names_[current_test_]
                 << ": " << success << " / " << total
                 << " (" << per << "%)\n\n";

    ts_success_ += success;
    ts_total_ += total;
}

std::ostream& TestSuite::summary_os_get()
{
    return *summary_os_;
}

std::ostream& TestSuite::details_os_get()
{
    return *details_os_;
}
