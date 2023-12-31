/**
 ** \file ast/dec.hh
 ** \brief Declaration of ast::Dec.
 */

#ifndef AST_DEC_HH
# define AST_DEC_HH

# include <ast/ast.hh>
# include <ast/typable.hh>
# include <misc/symbol.hh>

namespace ast
{

  /// Dec.
  class Dec : public Ast, public Typable
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Dec node.
    Dec(const Location& location, const misc::symbol& name);
    /// Destroy a Dec node.
    virtual ~Dec();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) override = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
  public:
    /// Return name of the defined entity.
    const misc::symbol& name_get() const;
    /// Set name of the defined entity.
    void name_set(const misc::symbol&);
    /** \} */

  protected:
    /// Name of the defined entity.
    misc::symbol name_;
  };

} // namespace ast

# include <ast/dec.hxx>

#endif // !AST_DEC_HH
