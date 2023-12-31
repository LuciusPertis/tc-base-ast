/**
 ** \file ast/decs.hh
 ** \brief Declare the interface for Decs class.
 */

#ifndef AST_DECS_HH
# define AST_DECS_HH

# include <list>

# include <ast/ast.hh>

namespace ast
{

  /// Declare Decs
  class Decs: public Ast
  {
    /** \name Ctors and dtors.
     ** \{ */
  public:
    /// Construct a Decs
    Decs(const Location& location);
    /// Destroy a Decs
    virtual ~Decs();
    /** \} */
  };

} // namespace ast

# include <ast/decs.hxx>

#endif // !AST_DECS_HH
