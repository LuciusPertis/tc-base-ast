/**
 ** \file tree/seq.cc
 ** \brief Implementation for tree/seq.hh.
 **/

#include <ostream>

#include <misc/indent.hh>
#include <tree/seq.hh>
#include <tree/trees.hh>

namespace tree
{
  Seq::Seq(const tree_list_type& children)
    : Stm()
    , children_(children)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  Seq::Seq(const rStm& left, const rStm& right)
    : Stm()
    , children_()
  {
    emplace_back(left);
    emplace_back(right);

    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  Seq::Seq(const rStm& left)
    : Stm()
    , children_()
  {
    emplace_back(left);
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

#ifndef SWIG
  Seq::Seq(std::initializer_list<rStm> l)
    : Stm()
    , children_()
  {
    for (const rStm& p : l)
      emplace_back(p);

    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }
#endif /* ! SWIG */

  std::ostream& Seq::tag_print(std::ostream&) const { unreachable(); }

  std::ostream& Seq::dump(std::ostream& ostr) const
  {
    return ostr << "seq" << misc::incendl << children_ << misc::decendl
                << "seq end";
  }

  void Seq::for_each_child(std::function<void(const rTree&)> f)
  {
    for (const auto& child : children_)
      f(child);
  }

  StmVariant Seq::variant(const rStm& ref) { return rSeq(ref.cast<Seq>()); }

} // namespace tree
