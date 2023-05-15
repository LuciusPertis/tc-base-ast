/**
 ** \file tree/sxp.hh
 ** \brief Intermediate representation: sxp.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>
#include <tree/stm.hh>

namespace tree
{
  /** \brief An expression which value is discarded.
   **
   ** Sxp is named EXP by A. Appel, but there are already too many Exp in
   ** this compiler.
   */
  class Sxp : public Stm
  {
  public:
    Sxp(const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Expression.
    rExp exp_get() const;

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

#include <tree/sxp.hxx>
