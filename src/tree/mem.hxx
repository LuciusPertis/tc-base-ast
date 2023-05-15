/**
 ** \file tree/mem.hxx
 ** \brief Inline methods for tree/mem.hh.
 **/

#pragma once

#include <tree/mem.hh>
#include <tree/temp.hh>

namespace tree
{
  inline rExp Mem::exp_get() const { return exp_; }

  inline void Mem::exp_set(const temp::Temp& temp)
  {
    exp_ = new tree::Temp(temp);
  }

} // namespace tree
