#pragma once

#include <set>
#include <string>
#include "ast.hh"
#include "model.hh"

namespace logic
{

  class PropositionalKB
  {

  public:

    PropositionalKB();
    ~PropositionalKB();

    void tell(const std::string& sentence);
    bool ask(const std::string& sentence);

  private:
    AST* kb_;

    /**
     * Check if the KB entails the sentence represented by ast
     * Enumerate all possible models
     * Returns true if in all model where KB is true ast is also true
     */
    bool check_all_(AST& ast, std::set<std::string>& symbols,
                    Model& model);
    
  };

}
