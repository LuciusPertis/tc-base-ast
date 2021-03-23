/**
 ** \file tree/name.cc
 ** \brief Implementation for tree/name.hh.
 **/

#include <ostream>

#include <temp/label.hh>
#include <tree/name.hh>

namespace tree
{
  Name::Name(const temp::Label& label)
    : label_(label)
  {}

  std::ostream& Name::tag_print(std::ostream& ostr) const
  {
    return ostr << "name " << label_;
  }

  std::ostream& Name::dump(std::ostream& ostr) const { return tag_print(ostr); }

  void Name::for_each_child(std::function<void(const rTree&)>) {}

  ExpVariant Name::variant(const rExp& ref) { return rName(ref.cast<Name>()); }

} // namespace tree
