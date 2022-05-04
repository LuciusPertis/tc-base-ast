/**
 ** \file tree/move.hxx
 ** \brief Inline methods for tree/move.hh.
 **/

#pragma once

#include <tree/move.hh>

namespace tree
{
  inline rExp Move::dst_get() const { return dst_; }

  inline rExp Move::src_get() const { return src_; }

} // namespace tree
