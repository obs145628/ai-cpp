#include "logic/propositional-kb.hh"
#include <sstream>
#include "logic/ast-and.hh"
#include "logic/eval-visitor.hh"
#include "logic/parser.hh"
#include "logic/symbols-visitor.hh"

namespace logic
{

  PropositionalKB::PropositionalKB()
    : kb_(nullptr)
  {}
  
  PropositionalKB::~PropositionalKB()
  {
    delete kb_;
  }

  void PropositionalKB::tell(const std::string& sentence)
  {
    std::istringstream is(sentence);
    Parser parser(is);
    AST* ast = parser.parse();

    if (kb_)
      kb_ = new ASTAnd(Token{"&", Token::Type::AND}, kb_, ast);
    else
      kb_ = ast;
  }
  
  bool PropositionalKB::ask(const std::string& sentence)
  {
    std::istringstream is(sentence);
    Parser parser(is);

    AST* ast = parser.parse();
    auto symbols = SymbolsVisitor::get(*kb_);
    for (const auto& sym : SymbolsVisitor::get(*ast))
      symbols.insert(sym);
    Model model;
    auto res = check_all_(*ast, symbols, model);

    delete ast;
    return res;
  }

  bool PropositionalKB::check_all_(AST& ast, std::set<std::string>& symbols,
                                   Model& model)
  {
    if (symbols.empty())
      return !EvalVisitor::eval(*kb_, model) || EvalVisitor::eval(ast, model);

    auto sym = symbols.begin();
    symbols.erase(sym);

    model.var_set(*sym, true);
    if (!check_all_(ast, symbols, model))
      return false;

    model.var_set(*sym, false);
    if (!check_all_(ast, symbols, model))
      return false;

    symbols.insert(*sym);
    return true;
  }
  
}
