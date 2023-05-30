/**
 ** \file canon/exp-matcher.hh
 ** \brief Definition of ExpMatcher.
 */

#pragma once

#include <canon/canon.hh>
#include <tree/fwd.hh>

namespace canon
{
  /// This corresponds to Appel's do_exp function.
  struct ExpMatcher
  {
    ExpMatcher() = delete;
    ExpMatcher(Canon* canon);

    using res_t = std::pair<tree::rSeq, tree::rExp>;

    res_t operator()(tree::rBinop e);
    res_t operator()(tree::rMem e);
    res_t operator()(tree::rEseq e);
    res_t operator()(tree::rCall e);
    res_t operator()(tree::rConst e);
    res_t operator()(tree::rName e);
    res_t operator()(tree::rTemp e);

  private:
    /// Default behavior.
    res_t default_match(tree::rExp e);
    /// The Canon object this visitor is part of.
    Canon* canon_;
  };
} // namespace canon
