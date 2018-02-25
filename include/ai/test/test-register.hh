#pragma once

#include <iostream>

class TestRegister
{
public:

    TestRegister();

    virtual void init() = 0;
    virtual void run() = 0;

    virtual int success_get() const = 0;
    virtual int total_get() const = 0;

protected:
    std::ostream& summary_os_;
    std::ostream& details_os_;
};
