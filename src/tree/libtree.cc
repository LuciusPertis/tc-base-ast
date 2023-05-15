/**
 ** \file tree/libtree.cc
 ** \brief Translate an AST into HIR.
 **/

#include <ostream>

#include <tree/fragments.hh>
#include <tree/libtree.hh>

namespace tree
{
  std::ostream& dump(const tree::Fragments& fragments, std::ostream& ostr)
  {
    return ostr << fragments;
  }

} // namespace tree
