/**
 ** \file tree/move.hh
 ** \brief Intermediate representation: move.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>
#include <tree/stm.hh>

namespace tree
{
  /// \brief Copy the content of the second operand to the first operand.
  class Move : public Stm
  {
  public:
    /** \brief Build a Move node.
     **
     ** \param dst      Memory indirection or register.
     ** \param src      Direct value, register or memory indirection.
     */
    Move(const rExp& dst, const rExp& src);

    /** \name Accessors.
     ** \{ */

    /// Destination.
    rExp dst_get() const;

    /// Source.
    rExp src_get() const;

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
    const rExp dst_;
    const rExp src_;
  };

} // namespace tree

#include <tree/move.hxx>
