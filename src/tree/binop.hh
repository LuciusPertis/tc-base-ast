/**
 ** \file tree/binop.hh
 ** \brief Intermediate representation: binop.hh
 **/

#ifndef TREE_BINOP_HH
# define TREE_BINOP_HH

# include <iosfwd>
# include <tree/exp.hh>

namespace tree
{

  class Binop : public Exp
  {
  public:
    /// Possible operations.
    enum Oper
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
    Binop (const Oper oper, const rExp& left, const rExp& right);

    /** \name Accessors.
     ** \{ */

    /// Left operand.
    rExp left_get () const;

    /// Right operand.
    rExp right_get () const;

    /// Operation.
    /// \see Oper.
    Oper oper_get () const;

    /** \} */

    /** \name Printing.
     ** \{ */

    virtual std::ostream& tag_print (std::ostream& ostr) const override;

    virtual kind_tree_type kind_get () const override;

    /** \} */

  private:
    Oper oper_;
  };

}

# include <tree/binop.hxx>

#endif // !TREE_BINOP_HH
