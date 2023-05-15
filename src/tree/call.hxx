/**
 ** \file tree/call.hxx
 ** \brief Inline methods for tree/call.hh.
 **/

#pragma once

#include <tree/call.hh>

namespace tree
{
  inline const rExp Call::func_get() const { return func_; }
  inline const tree_list_type& Call::args_get() const { return args_; }

} // namespace tree
