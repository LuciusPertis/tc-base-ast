/**
 ** \file tree/binop.hxx
 ** \brief Inline methods for tree/binop.hh.
 **/

#pragma once

#include <tree/binop.hh>

namespace tree
{
  inline rExp Binop::left_get() const { return left_.cast<Exp>(); }

  inline rExp Binop::right_get() const { return right_.cast<Exp>(); }

  inline Binop::Oper Binop::oper_get() const { return oper_; }

} // namespace tree
