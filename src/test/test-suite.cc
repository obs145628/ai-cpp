#include "test/test-suite.hh"
#include "shell/shell.hh"


const TestSuite::results_t& TestSuite::results_get()
{
  return results_;
}

const TestSuite::part_results_t& TestSuite::part_get()
{
  return part_results_;
}

void TestSuite::begin()
{

}

void TestSuite::end()
{
  int succ = 0;
  int total = 0;
  for (auto it : results_)
    {
      succ += count_part_succ_(it.second);
      total += it.second.size();
    }
  double percent = succ * 100.0 / total;

  std::cout << Shell::FG_YELLOW << Shell::BOLD
            << "Global results: "
            << succ << " / " << total << " (" << percent << "%)\n"
            << Shell::RESET;
}

void TestSuite::begin_part(const std::string& name)
{
  part_name_ = name;

  std::cout << Shell::FG_YELLOW << Shell::BOLD
            << name << ": \n\n" << Shell::RESET;
}

void TestSuite::end_part()
{
  results_.insert(std::make_pair(part_name_, part_results_));

  int succ = count_part_succ_(part_results_);
  int total = part_results_.size();
  double percent = succ * 100.0 / total;

  std::cout << "\n" << Shell::FG_YELLOW << Shell::BOLD
            << part_name_ << " results: "
            << succ << " / " << total << " (" << percent << "%)\n\n"
            << Shell::RESET;

  part_results_.clear();
}

void TestSuite::add_test_result(const std::string& name, bool res)
{
  part_results_[name] = res;
}

void TestSuite::option_disp_succ(bool b)
{
  opt_disp_succ_ = b;
}

int TestSuite::count_part_succ_(const part_results_t& part)
{
  int res = 0;
  for (auto it : part)
    res += it.second;
  return res;
}
