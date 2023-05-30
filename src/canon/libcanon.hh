/**
 ** \file canon/libcanon.hh
 ** \brief Simplify HIR into LIR.
 */

#pragma once

#include <tree/fwd.hh>

/// Simplification of tree::Tree code.
namespace canon
{
  /// Simplify the \a fragments.
  void canonicalize(tree::Fragments& fragments, bool canon_trace_p = false);

  /// Normalize the CJump of \a fragments.
  void make_traces(tree::Fragments& fragments, bool trace_trace_p = false);

} // namespace canon
