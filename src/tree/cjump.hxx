/**
 ** \file tree/cjump.hxx
 ** \brief Inline implementation of tree::Cjump.
 **/

#pragma once

#include <misc/contract.hh>
#include <temp/label.hh>
#include <tree/cjump.hh>

namespace tree
{
  inline rExp Cjump::left_get() const { return left_; }

  inline rExp Cjump::right_get() const { return right_; }

  inline temp::Label Cjump::label_true_get() const
  {
    const rName name = iftrue_.cast<Name>();
    return name->label_get();
  }

  inline temp::Label Cjump::label_false_get() const
  {
    const rName name = iffalse_.cast<Name>();
    return name->label_get();
  }

  inline void Cjump::label_false_set(const temp::Label& false_label)
  {
    iffalse_ = new Name(false_label);
  }

  inline temp::label_list_type Cjump::labels_get() const
  {
    temp::label_list_type res(label_true_get(), label_false_get());
    return res;
  }

  inline void Cjump::flip()
  {
    rName iftrue = iftrue_;
    iftrue_ = iffalse_;
    iffalse_ = iftrue;

    static const std::unordered_map<Relop, Relop> relop = {
      {Relop::eq, Relop::ne},   {Relop::ne, Relop::eq},
      {Relop::lt, Relop::ge},   {Relop::gt, Relop::le},
      {Relop::le, Relop::gt},   {Relop::ge, Relop::lt},
      {Relop::ult, Relop::uge}, {Relop::ugt, Relop::ule},
      {Relop::ule, Relop::ugt}, {Relop::uge, Relop::ult}};

    relop_ = relop.at(relop_);
  }

  inline const Cjump::Relop& Cjump::relop_get() const { return relop_; }

} // namespace tree
