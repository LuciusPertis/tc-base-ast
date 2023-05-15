/**
 ** \file tree/eseq.hh
 ** \brief Intermediate representation: eseq.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>
#include <tree/seq.hh>
#include <tree/stm.hh>

namespace tree
{
  class Eseq : public Exp
  {
  public:
    /** \brief Build a list of expressions.
     **
     ** \param stm      Statement list
     ** \param exp      Last expression
     */
    Eseq(const rStm& stm, const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Statement list
    rStm stm_get() const;

    /// Last expression
    rExp exp_get() const;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream&) const override;
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

    /// Iterating.
    void for_each_child(std::function<void(const rTree&)> f) override;

    /// Variant for matching.
    virtual ExpVariant variant(const rExp& ref) override;

  private:
    const rStm stm_;
    const rExp exp_;
  };

} // namespace tree

#include <tree/eseq.hxx>
