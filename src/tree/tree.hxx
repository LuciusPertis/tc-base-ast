/**
 ** \file tree/tree.hxx
 ** \brief Inline implementation of tree::Tree.
 **/

#pragma once

#include <algorithm>
#include <iostream>

#include <misc/contract.hh>
#include <misc/ref.hh>
#include <tree/tree.hh>

namespace tree
{
  inline Tree* Tree::parent_get() { return parent_; }

  inline const Tree* Tree::parent_get() const { return parent_; }

  inline void Tree::parent_set(Tree* parent) { parent_ = parent; }

  inline temp::Temp& Tree::asm_get()
  {
    if (not temp_)
      temp_ = new temp::Temp();
    return *temp_;
  }

  inline void Tree::asm_set(const temp::Temp& temp)
  {
    temp_ = new temp::Temp(temp);
  }

  inline void* Tree::state_get() const { return state_; }

  inline void*& Tree::state_get() { return state_; }

  inline bool Tree::reducible_get() const { return reducible_; }

  inline void Tree::reducible_set(bool b)
  {
    if (reducible_ == b)
      return;

    reducible_ = b;
    for_each_child([&](const rTree& child) { child->reducible_set(b); });
  }

  inline std::ostream& operator<<(std::ostream& ostr, const Tree& tree)
  {
    return tree.dump(ostr);
  }

} // namespace tree
