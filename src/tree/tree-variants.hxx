/**
 ** \file tree/tree-variants.hxx
 ** \brief Declaration of variant builders.
 **/

#pragma once

#include <misc/contract.hh>
#include <tree/exp.hh>
#include <tree/fwd.hh>
#include <tree/stm.hh>
#include <tree/tree-variants.hh>

namespace tree
{
  // This is not a particularly pretty function, but it does allow to generate
  // a variant on tree quite easily, which can be handy.
  // Another way could be to implement a method similar to variant in Exp and
  // Stm.
  inline TreeVariant make_tree_variant(tree::rTree t)
  {
    if (auto e = t.unsafe_cast<tree::Exp>())
      return e;
    if (auto e = t.unsafe_cast<tree::Stm>())
      return e;

    unreachable();
    return TreeVariant();
  }

} // namespace tree
