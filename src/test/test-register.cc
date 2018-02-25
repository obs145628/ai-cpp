#include "test/test-register.hh"
#include "test/test-suite.hh"

TestRegister::TestRegister()
    : summary_os_(TestSuite::Instance().summary_os_get())
    , details_os_(TestSuite::Instance().details_os_get())
{}

