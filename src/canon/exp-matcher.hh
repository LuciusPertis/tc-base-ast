/**
 ** \file canon/exp-matcher.hh
 ** \brief Definition of ExpMatcher.
 */

#pragma once

#include <canon/canon.hh>
#include <tree/fwd.hh>

namespace canon
{
  /// This corresponds to Appel's do_exp function. The main difference here
  /// is the return type: do_exp returns a pair containing the statements pulled
  /// out of the exp, and the modified exp. Instead of returning a pair, we
  /// return an Eseq.
  struct ExpMatcher
  {
    ExpMatcher() = delete;
    ExpMatcher(Canon* canon);

    tree::rEseq operator()(tree::rBinop e);
    tree::rEseq operator()(tree::rMem e);
    tree::rEseq operator()(tree::rEseq e);
    tree::rEseq operator()(tree::rCall e);
    tree::rEseq operator()(tree::rConst e);
    tree::rEseq operator()(tree::rName e);
    tree::rEseq operator()(tree::rTemp e);

  private:
    /// Default behavior.
    tree::rEseq default_match(tree::rExp e);
    /// The Canon object this visitor is part of.
    Canon* canon_;
  };
} // namespace canon
