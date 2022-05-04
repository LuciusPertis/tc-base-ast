/**
 ** \file tree/binop.hh
 ** \brief Intermediate representation: binop.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>

namespace tree
{
  class Binop : public Exp
  {
  public:
    /// Possible operations.
    enum class Oper
    {
      add,
      sub,
      mul,
      div,
      logic_and,
      logic_or,
      lshift,
      rshift,
      arshift,
      logic_xor
    };

    /** \brief Construct a Binary operator.
     **
     ** \param oper     Operation
     ** \param left     Left operand
     ** \param right    Right operand
     */
    Binop(const Oper oper, const rExp& left, const rExp& right);

    /** \name Accessors.
     ** \{ */

    /// Left operand.
    rExp left_get() const;

    /// Right operand.
    rExp right_get() const;

    /// Operation.
    /// \see Oper.
    Oper oper_get() const;

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
    Oper oper_;
    const rExp left_;
    const rExp right_;
  };

} // namespace tree

#include <tree/binop.hxx>
