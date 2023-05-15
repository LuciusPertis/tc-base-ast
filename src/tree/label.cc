/**
 ** \file tree/label.cc
 ** \brief Implementation for tree/label.hh
 **/

#include <ostream>

#include <temp/label.hh>
#include <tree/label.hh>

namespace tree
{
  Label::Label(const temp::Label& label)
    : Stm()
    , label_(label)
  {}

  std::ostream& Label::tag_print(std::ostream& ostr) const
  {
    return ostr << "label " << label_;
  }

  std::ostream& Label::dump(std::ostream& ostr) const
  {
    return tag_print(ostr);
  }

  void Label::for_each_child(std::function<void(const rTree&)>) {}

  StmVariant Label::variant(const rStm& ref)
  {
    return rLabel(ref.cast<Label>());
  }

} // namespace tree
