/**
 ** \file tree/mem.hh
 ** \brief Intermediate representation: mem.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>

namespace tree
{
  /** \brief Memory indirection.
   **
   ** Allow the access of the memory at a given address.
   */
  class Mem : public Exp
  {
  public:
    /** \brief Construct a memory indirection.
     **
     ** \param exp      Expression of accessed address.
     */
    Mem(const rExp& exp);

    /** \name Accessors.
     ** \{ */

    /// Accessed address.
    rExp exp_get() const;
    void exp_set(const temp::Temp& temp);

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

    /// Iterating.
    void for_each_child(std::function<void(const rTree&)> f) override;

    /// Variant for matching.
    virtual ExpVariant variant(const rExp& ref) override;

  private:
    rExp exp_;
  };

} // namespace tree

#include <tree/mem.hxx>
