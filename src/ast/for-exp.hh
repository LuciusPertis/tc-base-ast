/**
 ** \file ast/for-exp.hh
 ** \brief Declaration of ast::ForExp.
 */

#ifndef AST_FOR_EXP_HH
# define AST_FOR_EXP_HH

# include <ast/exp.hh>
# include <ast/var-dec.hh>

namespace ast
{

  /// ForExp.
  class ForExp : public Exp
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a ForExp node.
    ForExp(const Location& location, VarDec* vardec, Exp* hi, Exp* body);
    /// Destroy a ForExp node.
    virtual ~ForExp();
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
    /// Return implicit variable declaration.
    const VarDec& vardec_get() const;
    /// Return implicit variable declaration.
    VarDec& vardec_get();
    /// Return high bound of the loop.
    const Exp& hi_get() const;
    /// Return high bound of the loop.
    Exp& hi_get();
    /// Return instructions executed in the loop.
    const Exp& body_get() const;
    /// Return instructions executed in the loop.
    Exp& body_get();
    /** \} */

  protected:
    /// Implicit variable declaration.
    VarDec* vardec_;
    /// High bound of the loop.
    Exp* hi_;
    /// Instructions executed in the loop.
    Exp* body_;
  };

} // namespace ast

# include <ast/for-exp.hxx>

#endif // !AST_FOR_EXP_HH
