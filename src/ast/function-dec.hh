/**
 ** \file ast/function-dec.hh
 ** \brief Declaration of ast::FunctionDec.
 */

#ifndef AST_FUNCTION_DEC_HH
# define AST_FUNCTION_DEC_HH

# include <ast/exp.hh>
# include <ast/type-constructor.hh>
# include <ast/name-ty.hh>
# include <ast/dec.hh>
# include <ast/var-decs.hh>

namespace ast
{

  /// FunctionDec.
  class FunctionDec : public Dec, public TypeConstructor
  {

  public:
    /// Return the list of the escapes.
    std::list<bool> escapes_get() const
    {
  // FIXME: Some code was deleted here.
    }

    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a FunctionDec node.
    FunctionDec(const Location& location, const misc::symbol& name,
                VarDecs* formals, NameTy* result, Exp* body);
    /// Destroy a FunctionDec node.
    virtual ~FunctionDec();
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
    /// Return formal arguments.
    const VarDecs& formals_get() const;
    /// Return formal arguments.
    VarDecs& formals_get();
    /// Return result type.
    const NameTy* result_get() const;
    /// Return result type.
    NameTy* result_get();
    /// Return instructions.
    const Exp* body_get() const;
    /// Return instructions.
    Exp* body_get();
    /// Set instructions.
    void body_set(Exp*);
    /** \} */

  protected:
    /// Formal arguments.
    VarDecs* formals_;
    /// Result type.
    NameTy* result_;
    /// Instructions.
    Exp* body_;
  };

} // namespace ast

# include <ast/function-dec.hxx>

#endif // !AST_FUNCTION_DEC_HH
