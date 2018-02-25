#include "unit-test.hh"
#include <iomanip>
#include <iostream>
#include "shell/shell.hh"

template <class T>
void UnitTest<T>::run()
{
    max_names_size_ = 0;
    for (const auto& n : tests_names_)
	max_names_size_ = std::max(max_names_size_, n.size());
    max_names_size_ += 2;

    T* self = dynamic_cast<T*>(this);

    ut_success_ = 0;
    ut_total_ = 0;

    for (curr_test_ = 0; curr_test_ < tests_methods_.size(); ++curr_test_)
    {
        begin_test_();
        test_f fn = tests_methods_[curr_test_];
        ((*self).*fn)();
        end_test_();
    }
}

template <class T>
void UnitTest<T>::begin_test_()
{
    sucess_ = 0;
    total_ = 0;
}

template <class T>
void UnitTest<T>::end_test_()
{
    ut_success_ += sucess_;
    ut_total_ += total_;
    double acc = total_ == 0 ? 1 : sucess_ / double(total_);
    double per = acc * 100.0;
    per = int(per * 1000) / 1000.0;
    bool valid = sucess_ == total_;

    summary_os_ << tests_names_[curr_test_] << "...";
    for (std::size_t i = 0; i < max_names_size_ - tests_names_[curr_test_].size(); ++i)
	summary_os_ << ' ';

    if (valid)
	summary_os_ << Shell::FG_GREEN << "[OK] ";
    else
	summary_os_ << Shell::FG_RED << "[KO] ";

    summary_os_ << '[' << std::setfill('0') << std::setw(3) << sucess_
		<< '/' << std::setfill('0') << std::setw(3) << total_ << ']'
		<< Shell::FG_DEFAULT << std::endl;
    
	    //  summary_os_ << ": " << sucess_ << " / " << total_
	    //  << " (" << per << "%)\n";
}

template <class T>
void UnitTest<T>::check_(bool valid,
                         const char* file, const char* ex, int line)
{
    ++total_;
    if (valid)
    {
        ++sucess_;
        return;
    }

    summary_os_ << "Test " << total_ << " failed:\n"
                << file << "::" << line << ": " << ex << "\n";
}

template <class T>
template <class U>
void UnitTest<T>::check_eq_(const U& v1, const U& v2, const char* file,
			    const char* e1, const char* e2, int line)
{
    std::string expr = "(" + std::string(e1) + ") == (" + std::string(e2) + ")";
    check_(v1 == v2, file, expr.c_str(), line);
}

template <class T>
int UnitTest<T>::success_get() const
{
    return ut_success_;
}

template <class T>
int UnitTest<T>::total_get() const
{
    return ut_total_;
}

template <class T>
void UnitTest<T>::register_test(const std::string& name, test_f fn)
{
    tests_names_.push_back(name);
    tests_methods_.push_back(fn);
}


