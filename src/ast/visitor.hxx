/**
 ** \file ast/visitor.hxx
 ** \brief Definition of ast::Visitor.
 */

#ifndef AST_VISITOR_HXX
# define AST_VISITOR_HXX

# include <ast/visitor.hh>
# include <ast/ast.hh>

namespace ast
{
  template <template <typename> class Const>
  GenVisitor<Const>::~GenVisitor()
  {
  }

  template <template <typename> class Const>
  void
  GenVisitor<Const>::operator()(typename Const<ast::Ast>::type& e)
  {
    e.accept(*this);
  }

  template <template <typename> class Const>
  template <class E>
  void
  GenVisitor<Const>::operator()(E* e)
  {
    e->accept(*this);
  }

  template <template <typename> class Const>
  template <typename E>
  void
  GenVisitor<Const>::accept(E* e)
  {
    if (e)
      e->accept(*this);
  }

} // namespace ast

#endif // !AST_VISITOR_HXX
