/**
 ** \file tree/binop.cc
 ** \brief Implementation for tree/binop.hh.
 **/

#include <ostream>

#include <tree/binop.hh>

namespace tree
{
  Binop::Binop(const Oper oper, const rExp& left, const rExp& right)
    : oper_(oper)
    , left_(left)
    , right_(right)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Binop::tag_print(std::ostream& ostr) const
  {
    ostr << "binop ";

    static const std::unordered_map<Oper, std::string> oper = {
      {Oper::add, "add"},         {Oper::sub, "sub"},
      {Oper::mul, "mul"},         {Oper::div, "div"},
      {Oper::logic_and, "and"},   {Oper::logic_or, "or"},
      {Oper::lshift, "lshft"},    {Oper::rshift, "rshift"},
      {Oper::arshift, "arshift"}, {Oper::logic_xor, "xor"}};

    return ostr << oper.at(oper_);
  }

  std::ostream& Binop::dump(std::ostream& ostr) const
  {
    tag_print(ostr);

    return ostr << misc::incendl << *left_ << misc::iendl << *right_
                << misc::decindent;
  }

  void Binop::for_each_child(std::function<void(const rTree&)> f)
  {
    f(left_);
    f(right_);
  }

  ExpVariant Binop::variant(const rExp& ref)
  {
    return rBinop(ref.cast<Binop>());
  }

} // namespace tree
