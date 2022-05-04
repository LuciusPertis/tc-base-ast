/**
 ** \file tree/jump.hh
 ** \brief Declaration of tree::Jump.
 **/

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <tree/exp.hh>
#include <tree/stm.hh>

namespace tree
{
  /// Inconditional branching.
  ///
  /// Our tree::Jump instruction is simpler than Appel's, which
  /// requires a list of all the possible destinations (for later
  /// dataflow analysis).  Our implementation assumes the expression
  /// used as a destination is always a tree::Name.  Therefore,
  /// tree::Name::label_get always returns a singleton list.
  class Jump : public Stm
  {
  public:
    Jump(const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// The destination.
    rExp exp_get() const;

    /// The list of destination labels.
    temp::label_list_type label_get() const;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

    /// Iterating.
    void for_each_child(std::function<void(const rTree&)> f) override;

    /// Variant for matching.
    virtual StmVariant variant(const rStm& ref) override;

  private:
    const rExp exp_;
  };

} // namespace tree

#include <tree/jump.hxx>
