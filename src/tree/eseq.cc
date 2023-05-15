/**
 ** \file tree/eseq.cc
 ** \brief Implementation for tree/eseq.hh.
 **/

#include <ostream>

#include <misc/indent.hh>
#include <tree/eseq.hh>

namespace tree
{
  Eseq::Eseq(const rStm& stm, const rExp& exp)
    : Exp()
    , stm_(stm)
    , exp_(exp)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Eseq::tag_print(std::ostream&) const { unreachable(); }

  std::ostream& Eseq::dump(std::ostream& ostr) const
  {
    ostr << "eseq";
    // If the stm is a seq, don't increment again.
    if (stm_.is_a<Seq>())
      ostr << misc::iendl << *stm_ << misc::incendl;
    else
      ostr << misc::incendl << *stm_ << misc::iendl;
    return ostr << *exp_ << misc::decindent;
  }

  void Eseq::for_each_child(std::function<void(const rTree&)> f)
  {
    f(stm_);
    f(exp_);
  }

  ExpVariant Eseq::variant(const rExp& ref) { return rEseq(ref.cast<Eseq>()); }

} // namespace tree
