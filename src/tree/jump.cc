/**
 ** \file tree/jump.cc
 ** \brief Implementation of tree::Jump.
 **/

#include <ostream>

#include <tree/jump.hh>

namespace tree
{
  Jump::Jump(const rExp& exp)
    : Stm()
    , exp_(exp)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Jump::tag_print(std::ostream& ostr) const
  {
    return ostr << "jump";
  }

  std::ostream& Jump::dump(std::ostream& ostr) const
  {
    tag_print(ostr);
    return ostr << misc::incendl << *exp_ << misc::decindent;
  }

  void Jump::for_each_child(std::function<void(const rTree&)> f) { f(exp_); }

  StmVariant Jump::variant(const rStm& ref) { return rJump(ref.cast<Jump>()); }

} // namespace tree
