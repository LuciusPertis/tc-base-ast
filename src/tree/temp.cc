/**
 ** \file tree/temp.cc
 ** \brief Implementation for tree/temp.hh.
 **/

#include <temp/temp.hh>
#include <tree/temp.hh>

namespace tree
{
  Temp::Temp(const temp::Temp& temp)
    : temp_(temp)
  {}

  std::ostream& Temp::tag_print(std::ostream& ostr) const
  {
    return ostr << "temp " << temp_;
  }

  std::ostream& Temp::dump(std::ostream& ostr) const { return tag_print(ostr); }

  void Temp::for_each_child(std::function<void(const rTree&)>) {}

  ExpVariant Temp::variant(const rExp& ref) { return rTemp(ref.cast<Temp>()); }

} // namespace tree
