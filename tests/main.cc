#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "shell.hh"
#include "test.hh"

int main()
{

  TestSuite ts;

  ts.begin();

  ts.begin_part("Calcul");

  ts.add_equal_test("addition", 1 + 2, 3);
  ts.add_equal_test("division", double(5 / 2), 2.5);
  ts.add_equal_test("multiplication", 3 * 2, 6);

  ts.end_part();

  ts.begin_part("String");

  ts.add_equal_test("empty count", 0, -1);
  ts.add_equal_test("reverse", std::string(".cba"), std::string("cba"));
  ts.add_equal_test("toupper", std::string("TEST56"), std::string("TEST56"));

  ts.end_part();

  ts.end();

}
