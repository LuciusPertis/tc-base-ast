/**
 ** \file tree/mem.cc
 ** \brief Implementation for tree/mem.hh.
 **/

#include <ostream>

#include <tree/mem.hh>

namespace tree
{
  Mem::Mem(const rExp& exp)
    : Exp()
    , exp_(exp)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Mem::tag_print(std::ostream& ostr) const
  {
    return ostr << "mem";
  }

  std::ostream& Mem::dump(std::ostream& ostr) const
  {
    tag_print(ostr);
    return ostr << misc::incendl << *exp_ << misc::decindent;
  }

  void Mem::for_each_child(std::function<void(const rTree&)> f) { f(exp_); }

  ExpVariant Mem::variant(const rExp& ref) { return rMem(ref.cast<Mem>()); }

} // namespace tree
