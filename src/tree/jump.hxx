/**
 ** \file tree/jump.hxx
 ** \brief Inline implementation of tree::Jump.
 **/

#pragma once

#include <temp/label.hh>
#include <tree/jump.hh>
#include <tree/name.hh>

namespace tree
{
  inline rExp Jump::exp_get() const { return exp_; }

  inline temp::label_list_type Jump::label_get() const
  {
    return {exp_.cast<Name>()->label_get()};
  }

} //namespace tree
