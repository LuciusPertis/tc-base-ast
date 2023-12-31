/**
 ** \file ast/cast-var.hh
 ** \brief Declaration of ast::CastVar.
 */

#ifndef AST_CAST_VAR_HH
# define AST_CAST_VAR_HH

# include <ast/var.hh>
# include <ast/ty.hh>

namespace ast
{


  /** \class ast::CastVar
   ** \brief Cast the type of an l-value to a given type.
   **
   ** This node is only used in the bound checking transformation
   ** (see desugar::bound_checks_add).  You don't need to worry
   ** about it (nor about the `cast' keyword) if you don't implement
   ** this option.
   */

  class CastVar : public Var
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a CastVar node.
    CastVar(const Location& location, Var* var, Ty* ty);
    /// Destroy a CastVar node.
    virtual ~CastVar();
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
    /// Return the cast variable.
    const Var& var_get() const;
    /// Return the cast variable.
    Var& var_get();
    /// Return the target type.
    const Ty& ty_get() const;
    /// Return the target type.
    Ty& ty_get();
    /** \} */

  protected:
    /// The cast variable.
    Var* var_;
    /// The target type.
    Ty* ty_;
  };

} // namespace ast

# include <ast/cast-var.hxx>

#endif // !AST_CAST_VAR_HH
