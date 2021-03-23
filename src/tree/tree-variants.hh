/**
 ** \file tree/tree-variants.hh
 ** \brief Definition of variants on Tree nodes.
 **/

#pragma once

#include <misc/variant.hh>
#include <tree/fwd.hh>

namespace tree
{
  /// These Variant classes are to be used as a layer over rTrees, which will
  /// allow their use with std::visit in order to perform pattern-matching.

  using TreeVariant = misc::variant<rExp, rStm>;

  using ExpVariant =
    misc::variant<rBinop, rCall, rConst, rEseq, rMem, rName, rTemp>;

  using StmVariant = misc::variant<rCjump, rJump, rLabel, rMove, rSeq, rSxp>;

  /// Create a TreeVariant out of \a t.
  TreeVariant make_tree_variant(tree::rTree t);

} // namespace tree

#include <tree/tree-variants.hxx>
