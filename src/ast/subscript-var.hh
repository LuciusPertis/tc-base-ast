/**
 ** \file ast/subscript-var.hh
 ** \brief Declaration of ast::SubscriptVar.
 */

#ifndef AST_SUBSCRIPT_VAR_HH
# define AST_SUBSCRIPT_VAR_HH

# include <ast/exp.hh>
# include <ast/var.hh>

namespace ast
{

  /// SubscriptVar.
  class SubscriptVar : public Var
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a SubscriptVar node.
    SubscriptVar(const Location& location, Var* var, Exp* index);
    /// Destroy a SubscriptVar node.
    virtual ~SubscriptVar();
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
    /// Return the mother variable.
    const Var& var_get() const;
    /// Return the mother variable.
    Var& var_get();
    /// Return the offset expression.
    const Exp& index_get() const;
    /// Return the offset expression.
    Exp& index_get();
    /** \} */

  protected:
    /// The mother variable.
    Var* var_;
    /// The offset expression.
    Exp* index_;
  };

} // namespace ast

# include <ast/subscript-var.hxx>

#endif // !AST_SUBSCRIPT_VAR_HH
