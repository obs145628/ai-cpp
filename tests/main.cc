#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <sstream>

#include "shell.hh"
#include "math.hh"
#include "logic.hh"

using KB = logic::PropositionalKB;

int main()
{

  std::string data = "(a & b => !a) | d & !(c & d)";
  std::istringstream is(data);
  logic::Parser parser(is);
  auto ast = parser.parse();
  ast = logic::CNF::build(*ast);
  logic::PrintVisitor::print(std::cout, *ast);
  delete ast;

  return 0;
  KB kb;

  kb.tell("a => b");
  kb.tell("!b");

  std::cout << "a: " << kb.ask("a") << std::endl;
  std::cout << "!a: " << kb.ask("!a") << std::endl;
  std::cout << "b: " << kb.ask("b") << std::endl;
  std::cout << "!b: " << kb.ask("!b") << std::endl;
}
