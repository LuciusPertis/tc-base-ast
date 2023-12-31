/**
 ** \file ast/decs-list.hh
 ** \brief Declaration of ast::DecsList.
 */

#ifndef AST_DECS_LIST_HH
# define AST_DECS_LIST_HH

# include <ast/ast.hh>

namespace ast
{

  /// DecsList.
  class DecsList : public Ast
  {
  public:
    typedef std::list<Decs*> decs_type;

    /// Prepend \a d.
    void push_front(Decs* d);
    /// Append \a d.
    void push_back(Decs* d);

    /// Splice the content of \a ds in front of this list.
    void splice_front(DecsList& ds);
    /// Splice the content of \a ds at the back this list.
    void splice_back(DecsList& ds);

    /// Construct a DecsList node.
    DecsList(const Location& location);

    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a DecsList node.
    DecsList(const Location& location, const DecsList::decs_type& decs);
    /// Destroy a DecsList node.
    virtual ~DecsList();
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
    /// Return declarations.
    const DecsList::decs_type& decs_get() const;
    /// Return declarations.
    DecsList::decs_type& decs_get();
    /** \} */

  protected:
    /// Declarations.
    DecsList::decs_type decs_;
  };

} // namespace ast

# include <ast/decs-list.hxx>

#endif // !AST_DECS_LIST_HH
