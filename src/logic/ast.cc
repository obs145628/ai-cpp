#include "logic/ast.hh"
#include <cassert>

namespace logic
{

  AST::AST(const Token& token, const std::vector<AST*>& children)
    : token_(token)
    , children_(children)
  {}
  
  AST::~AST()
  {
    for (auto child : children_)
      delete child;
  }

  std::size_t AST::count()
  {
    return children_.size();
  }
  
  const AST& AST::child_get(std::size_t i) const
  {
    assert(i < children_.size());
    return *(children_[i]);
  }
  
  AST& AST::child_get(std::size_t i)
  {
    assert(i < children_.size());
    return *(children_[i]);
  }

  const std::vector<AST*>& AST::children_get() const
  {
    return children_;
  }
  
  std::vector<AST*>& AST::children_get()
  {
    return children_;
  }

  const Token& AST::token_get() const
  {
    return token_;
  }
  
  Token& AST::token_get()
  {
    return token_;
  }

  std::vector<AST*> AST::detach()
  {
    auto res = children_;
    children_.clear();
    return res;
  }
  
}
