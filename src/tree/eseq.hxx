/**
 ** \file tree/eseq.hxx
 ** \brief Inline methods for tree/eseq.hh.
 **/

#pragma once

#include <tree/eseq.hh>

namespace tree
{
  inline rStm Eseq::stm_get() const { return stm_; }

  inline rExp Eseq::exp_get() const { return exp_; }

} // namespace tree
