/**
 ** \file overload/liboverload.hh
 ** \brief Declare functions and variables exported by overload module.
 */

#ifndef OVERLOAD_LIBOVERLOAD_HH
# define OVERLOAD_LIBOVERLOAD_HH

# include <misc/error.hh>
# include <ast/fwd.hh>
# include <overload/binder.hh>

/**
 ** \brief Perform type checking, allowing function overloading.
 */
namespace overload
{

  /** \brief Bind identifier uses to their definition, allowing
      function overloading, and return a list of potential definition
      sites for each function call.

      \param tree AST to bind.

      \return a pair whose first element is the potential function
              bindings, and the second element the error status.  */
  std::pair<overload::overfun_bindings_type*, misc::error>
  bind(ast::Ast& tree);

  /** \brief Check types allowing function overloading.

      \param tree             abstract syntax tree's root.
      \param overfun_bindings potential function bindings.

      \return success of the type-checking.  */
  misc::error
  types_check(ast::Ast& tree,
              overload::overfun_bindings_type* overfun_bindings);

} // namespace overload

#endif // !OVERLOAD_LIBOVERLOAD_HH
