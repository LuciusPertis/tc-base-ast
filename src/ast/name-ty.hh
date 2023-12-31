/**
 ** \file ast/name-ty.hh
 ** \brief Declaration of ast::NameTy.
 */

#ifndef AST_NAME_TY_HH
# define AST_NAME_TY_HH

# include <ast/type-dec.hh>
# include <ast/ty.hh>
# include <misc/symbol.hh>

namespace ast
{

  /// NameTy.
  class NameTy : public Ty
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a NameTy node.
    NameTy(const Location& location, const misc::symbol& name);
    /// Destroy a NameTy node.
    virtual ~NameTy();
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
    /// Return the name of the type.
    const misc::symbol& name_get() const;
    /// Set the name of the type.
    void name_set(const misc::symbol&);
    /// Return definition site.
    const TypeDec* def_get() const;
    /// Return definition site.
    TypeDec* def_get();
    /// Set definition site.
    void def_set(TypeDec*);
    /** \} */

  protected:
    /// The name of the type.
    misc::symbol name_;
    /// Definition site.
    TypeDec* def_ = nullptr;
  };

} // namespace ast

# include <ast/name-ty.hxx>

#endif // !AST_NAME_TY_HH
