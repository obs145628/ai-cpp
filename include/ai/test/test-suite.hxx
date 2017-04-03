#pragma once

#include "test-suite.hh"
#include <iostream>
#include "../shell/shell.hh"

template <class T>
void TestSuite::add_equal_test(const std::string& name,
                               const T& ref, const T& me)
{

  bool res = ref == me;

  if (res && opt_disp_succ_)
    {
      std::cout << Shell::FG_MAGENTA << name << "... ";
      std::cout << Shell::FG_GREEN << "[SUCCESS]\n" << Shell::RESET;
    }
  
  if (!res)
    {
      std::cout << Shell::FG_MAGENTA << name << "... ";
      std::cout << Shell::FG_RED << "[FAILLURE]\n";
      std::cout << " me: <<" << me << ">>\n";
      std::cout << "ref: <<" << ref << ">>\n";
      std::cout << Shell::RESET;
    }

  add_test_result(name, res);
}
