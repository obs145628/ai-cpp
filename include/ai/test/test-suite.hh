#pragma once

#include <map>
#include <string>
#include <vector>

class TestSuite
{

public:

  using part_results_t = std::map<std::string, bool>;
  using results_t = std::map<std::string, part_results_t>;

  void begin();
  void end();

  void begin_part(const std::string& name);
  void end_part();

  template <class T>
  void add_equal_test(const std::string& name,
                      const T& ref, const T& me);

  void add_test_result(const std::string& name, bool res);

  void option_disp_succ(bool b);

private:
  results_t results_;
  part_results_t part_results_;
  std::string part_name_;
  bool opt_disp_succ_ = true;

  static int count_part_succ_(const part_results_t& part);
  
};

#include "test-suite.hxx"
