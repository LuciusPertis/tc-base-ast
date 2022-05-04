/**
 ** \file tree/const.cc
 ** \brief Implementation for tree/const.hh.
 **/

#include <ostream>

#include <tree/const.hh>

namespace tree
{
  Const::Const(int value)
    : value_(value)
  {}

  std::ostream& Const::tag_print(std::ostream& ostr) const
  {
    return ostr << "const " << value_;
  }

  std::ostream& Const::dump(std::ostream& ostr) const
  {
    return tag_print(ostr);
  }

  void Const::for_each_child(std::function<void(const rTree&)>) {}

  ExpVariant Const::variant(const rExp& ref)
  {
    return rConst(ref.cast<Const>());
  }

} // namespace tree
