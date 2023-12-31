/**
 ** \file bind/renamer.hh
 ** \brief Implementation of bind::Renamer.
 */

#ifndef BIND_RENAMER_HH
# define BIND_RENAMER_HH

# include <map>
# include <ast/default-visitor.hh>
# include <ast/non-object-visitor.hh>

namespace bind
{
  /// Perform identifier renaming within an AST (in place),
  /// without support for objects.
  class Renamer : public ast::DefaultVisitor, public ast::NonObjectVisitor
  {
  public:
    typedef ast::DefaultVisitor super_type;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a Renamer.
    Renamer();

    /// \name Auxiliary routines.
    /// \{
    /// \brief Compute the name for this kind of declaration.
    ///
    /// Take into account the fact that _main and primitive are
    /// not to be renamed.
    template <typename Def>
    misc::symbol new_name_compute(const Def& e);

    /// \brief Get the new name of this declaration, possibly create it.
    ///
    /// The tricky thing is that when visiting a chunk of definitions,
    /// we might visit a body using a name not yet renamed (e.g., mutually
    /// recursive functions), in which case we must compute the
    /// new name of that function on the fly.
    template <typename Def>
    misc::symbol new_name(const Def& e);
    /// \}

    // Visit methods.
  public:
    /// \brief Process a declaration body or a usage site.
    ///
    /// \a def is the definition site of \e (must be equal to
    /// \a e if it is a Dec node).
    template <class E, class Def>
    void visit(E& e, const Def* def);

    /// \name Visiting definition sites.
    /// \{
  // FIXME: Some code was deleted here.
    /// \}

    /// \name Visiting usage sites.
    /// \{
  // FIXME: Some code was deleted here.
    /// \}

  private:
    /// \name New names.
    /// \{
    /// New names associated to original declared entities.
    typedef std::map<const ast::Dec*, misc::symbol> new_names_type;
    /// Dictionnary mapping old declarations to their new names.
    new_names_type new_names_;
    /// \}
  };

} // namespace bind

# include <bind/renamer.hxx>

#endif // !BIND_RENAMER_HH
