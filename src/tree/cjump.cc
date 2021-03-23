/**
 ** \file tree/cjump.cc
 ** \brief Implementation of tree::Cjump.
 **/

#include <ostream>

#include <tree/cjump.hh>

namespace tree
{
  Cjump::Cjump(Relop relop,
               const rExp& left,
               const rExp& right,
               rName& iftrue,
               rName& iffalse)
    : Stm()
    , relop_(relop)
    , left_(left)
    , right_(right)
    , iftrue_(iftrue)
    , iffalse_(iffalse)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  Cjump::Cjump(Relop relop,
               const rExp& left,
               const rExp& right,
               const temp::Label& iftrue,
               const temp::Label& iffalse)
    : Stm()
    , relop_(relop)
    , left_(left)
    , right_(right)
    , iftrue_(new tree::Name((iftrue)))
    , iffalse_(new tree::Name((iffalse)))
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Cjump::tag_print(std::ostream& ostr) const
  {
    ostr << "cjump " << relop_;
    return ostr;
  }

  std::ostream& Cjump::dump(std::ostream& ostr) const
  {
    tag_print(ostr);
    return ostr << misc::incendl << *left_ << misc::iendl << *right_
                << misc::iendl << *iftrue_ << misc::iendl << *iffalse_
                << misc::decindent;
  }

  Cjump::Relop symmetrize(const Cjump::Relop& r)
  {
    static const std::unordered_map<Cjump::Relop, Cjump::Relop> relop = {
      {Cjump::Relop::eq, Cjump::Relop::eq},
      {Cjump::Relop::ne, Cjump::Relop::ne},
      {Cjump::Relop::lt, Cjump::Relop::gt},
      {Cjump::Relop::gt, Cjump::Relop::lt},
      {Cjump::Relop::le, Cjump::Relop::ge},
      {Cjump::Relop::ge, Cjump::Relop::le},
      {Cjump::Relop::ult, Cjump::Relop::ugt},
      {Cjump::Relop::ugt, Cjump::Relop::ult},
      {Cjump::Relop::ule, Cjump::Relop::uge},
      {Cjump::Relop::uge, Cjump::Relop::ule}};

    auto relop_it = relop.find(r);
    if (relop_it == relop.end())
      die("Should not be here.");
    else
      return relop_it->second;
  }

  std::ostream& operator<<(std::ostream& ostr, const Cjump::Relop& r)
  {
    static const std::unordered_map<Cjump::Relop, std::string> relop = {
      {Cjump::Relop::eq, "eq"},   {Cjump::Relop::ne, "ne"},
      {Cjump::Relop::lt, "lt"},   {Cjump::Relop::gt, "gt"},
      {Cjump::Relop::le, "le"},   {Cjump::Relop::ge, "ge"},
      {Cjump::Relop::ult, "ult"}, {Cjump::Relop::ugt, "ugt"},
      {Cjump::Relop::ule, "ule"}, {Cjump::Relop::uge, "uge"}};

    return ostr << relop.at(r);
  }

  inline void Cjump::for_each_child(std::function<void(const rTree&)> f)
  {
    f(left_);
    f(right_);
    f(iftrue_);
    f(iffalse_);
  }

  StmVariant Cjump::variant(const rStm& ref)
  {
    return rCjump(ref.cast<Cjump>());
  }

} // namespace tree
