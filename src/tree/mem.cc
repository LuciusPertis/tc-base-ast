/**
 ** \file tree/mem.cc
 ** \brief Implementation for tree/mem.hh.
 **/

#include <ostream>

#include <tree/mem.hh>

namespace tree
{

  std::ostream&
  Mem::tag_print(std::ostream& ostr) const
  {
    return ostr << "mem";
  }

  Tree::kind_tree_type
  Mem::kind_get() const
  {
    return mem_kind;
  }

}
