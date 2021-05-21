/**
 ** \file assem/layout.hxx
 ** \brief Inline methods for assem/layout.hh.
 */

#pragma once

#include <assem/layout.hh>

namespace assem
{
  inline Layout::Layout()
    : postr_(nullptr)
  {}

  inline void Layout::ostr_set(std::ostream& ostr) { postr_ = &ostr; }

} // namespace assem
