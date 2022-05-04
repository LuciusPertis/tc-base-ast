/**
 ** \file tree/move.cc
 ** \brief Implementation for tree/move.hh.
 **/

#include <ostream>

#include <tree/move.hh>

namespace tree
{
  Move::Move(const rExp& dst, const rExp& src)
    : Stm()
    , dst_(dst)
    , src_(src)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Move::tag_print(std::ostream& ostr) const
  {
    return ostr << "move";
  }

  std::ostream& Move::dump(std::ostream& ostr) const
  {
    tag_print(ostr);
    return ostr << misc::incendl << *dst_ << misc::iendl << *src_
                << misc::decindent;
  }

  void Move::for_each_child(std::function<void(const rTree&)> f)
  {
    f(dst_);
    f(src_);
  }

  StmVariant Move::variant(const rStm& ref) { return rMove(ref.cast<Move>()); }

} // namespace tree
