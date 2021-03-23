/**
 ** \file tree/seq.hxx
 ** \brief Inline methods for tree/seq.hh.
 **/

#pragma once

#include <tree/seq.hh>

namespace tree
{
  inline void Seq::emplace_back(const rStm& stm)
  {
    rTree tree = stm;
    children_.emplace_back(tree);
  }

  inline tree_list_type& Seq::children_get() { return children_; }

  inline const tree_list_type& Seq::children_get() const { return children_; }

} // namespace tree
