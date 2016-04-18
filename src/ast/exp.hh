/**
 ** \file ast/exp.hh
 ** \brief Declaration of ast::Exp.
 */

#pragma once

#include <ast/ast.hh>
#include <ast/typable.hh>

namespace ast
{

  /// Exp.
  class Exp : public Ast, public Typable
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct an Exp node.
    Exp(const Location& location);
    /// Destroy an Exp node.
    virtual ~Exp();
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
  public:
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const override = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) override = 0;
    /// \}
  };

} // namespace ast

#include <ast/exp.hxx>

