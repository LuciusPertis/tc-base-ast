/**
 ** \file canon/stm-matcher.hh
 ** \brief Definition of StmMatcher.
 */

#pragma once

#include <canon/canon.hh>
#include <tree/fwd.hh>

namespace canon
{
  /// This corresponds to Appel's do_stm function.
  struct StmMatcher
  {
    StmMatcher() = delete;
    StmMatcher(Canon* canon);

    tree::rSeq operator()(tree::rSeq e);
    tree::rSeq operator()(tree::rJump e);
    tree::rSeq operator()(tree::rCjump e);
    tree::rSeq operator()(tree::rMove e);
    tree::rSeq operator()(tree::rSxp e);
    tree::rSeq operator()(tree::rLabel e);

  private:
    /// Default behavior.
    tree::rSeq default_match(tree::rStm e);

    /// The Canon object this visitor is part of.
    Canon* canon_;
  };
} // namespace canon
