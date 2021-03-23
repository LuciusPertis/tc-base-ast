/**
 ** \file tree/sxp.cc
 ** \brief Implementation for tree/sxp.hh.
 **/

#include <ostream>

#include <tree/sxp.hh>

namespace tree
{
  Sxp::Sxp(const rExp& exp)
    : Stm()
    , exp_(exp)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Sxp::tag_print(std::ostream& ostr) const
  {
    return ostr << "sxp";
  }

  std::ostream& Sxp::dump(std::ostream& ostr) const
  {
    tag_print(ostr);
    return ostr << misc::incendl << *exp_ << misc::decindent;
  }

  void Sxp::for_each_child(std::function<void(const rTree&)> f) { f(exp_); }

  StmVariant Sxp::variant(const rStm& ref) { return rSxp(ref.cast<Sxp>()); }

} // namespace tree
