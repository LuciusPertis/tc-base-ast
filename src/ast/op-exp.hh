/**
 ** \file ast/op-exp.hh
 ** \brief Declaration of ast::OpExp.
 */

#ifndef AST_OP_EXP_HH
# define AST_OP_EXP_HH

# include <ast/exp.hh>

namespace ast
{

  /// OpExp.
  class OpExp : public Exp
  {

  public:
    /// Operator qualifier.
    enum Oper
      {
        // Arithmetics.
        /** \brief "+" */ add,
        /** \brief "-" */ sub,
        /** \brief "*" */ mul,
        /** \brief "/" */ div,

        // Comparison.
        /** \brief "=" */  eq,
        /** \brief "<>" */ ne,
        /** \brief "<" */  lt,
        /** \brief "<=" */ le,
        /** \brief ">" */  gt,
        /** \brief ">=" */ ge
      };

    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct an OpExp node.
    OpExp(const Location& location, Exp* left, OpExp::Oper oper,
          Exp* right);
    /// Destroy an OpExp node.
    virtual ~OpExp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
  public:
    /// Return left operand.
    const Exp& left_get() const;
    /// Return left operand.
    Exp& left_get();
    /// Return operator.
    OpExp::Oper oper_get() const;
    /// Return right operand.
    const Exp& right_get() const;
    /// Return right operand.
    Exp& right_get();
    /** \} */

  protected:
    /// Left operand.
    Exp* left_;
    /// Operator.
    OpExp::Oper oper_;
    /// Right operand.
    Exp* right_;
  };

} // namespace ast


// Return a representation of an operator.
std::string
str(ast::OpExp::Oper oper);

# include <ast/op-exp.hxx>

#endif // !AST_OP_EXP_HH
