/**
 ** \file tree/tree.cc
 ** \brief Implementation of tree::Tree.
 **/

#include <iostream>

#include <misc/indent.hh>
#include <range/v3/algorithm/find.hpp>
#include <tree/tree.hh>
#include <tree/trees.hh>

namespace tree
{
  Tree::Tree() {}

  Tree::~Tree() { delete temp_; }

  void Tree::parent_get_assert() const
  {
    if (parent_ == nullptr)
      {
        std::cerr << "This tree has no parent:" << misc::incendl << *this
                  << misc::decindent;
        precondition(parent_ != nullptr);
      }
  }

} // namespace tree
