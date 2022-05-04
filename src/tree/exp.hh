/**
 ** \file tree/exp.hh
 ** \brief Intermediate representation: exp.hh
 **/

#pragma once

#include <tree/tree-variants.hh>
#include <tree/tree.hh>

namespace tree
{
  /** \brief Node that has a value, contrary to \a Stm.
   ** \see tree::Stm.
   */
  class Exp : public Tree
  {
  public:
    /** \brief Make a variant out of this node.
     ** Note that we have \a ref as an argument in order to propagate the use
     ** count of the shared pointers on this node. If we were to construct a
     ** misc::ref on this node without copying it from another ref, its use
     ** count would be different which would be problematic. */
    virtual ExpVariant variant(const rExp& ref) = 0;
  };

} // namespace tree
