/**
 ** \file parse/tweast.hh
 ** \brief Declaration of parse::Tweast.
 */

#ifndef PARSE_TWEAST_HH
# define PARSE_TWEAST_HH

# include <map>
# include <iostream>
# include <sstream>
# include <ast/fwd.hh>
# include <misc/symbol.hh>
# include <misc/map.hh>
# include <parse/metavar-map.hh>

namespace parse
{
  /// \brief TWEAST stands for ``Text With Embedded Abstract Syntax Trees''.
  ///
  /// Aggregate string to parse and tables of metavariables.
  class Tweast
    : public MetavarMap<ast::Exp>
    , public MetavarMap<ast::Var>
    , public MetavarMap<ast::NameTy>
    , public MetavarMap<ast::DecsList>
    , public MetavarMap<parse::Tweast>
  {
  public:
    Tweast();
    Tweast(const std::string& str);
    virtual ~Tweast();

    /// \brief Stream manipulator.
    ///
    /// Append Tiger expressions to the string to parse.
    template <typename T> Tweast& operator<< (const T& t);

    /// Metavariables manipulator.
    template <typename T> T* take(unsigned s);

    /// Move the contents of all aggregated Tweast metavariables into
    /// the current Tweast.
    void flatten();

    /// Get the current input string.
    std::string input_get() const;

    /// Print the table
    std::ostream& dump(std::ostream& ostr) const;

  protected:
    // Insert base class append members in the current scope.
    using MetavarMap<ast::Exp>::append_;
    using MetavarMap<ast::Var>::append_;
    using MetavarMap<ast::NameTy>::append_;
    using MetavarMap<ast::DecsList>::append_;
    using MetavarMap<Tweast>::append_;

    /// Fake append (default case, i.e. when \a data is not a metavariable).
    template <typename T> T& append_(unsigned&, T& data) const;

    template <typename T>
    void move_metavars_(Tweast& tweast, std::string& input);

  protected:
    /// The next identifier suffix to create.
    static unsigned count_;

    /// The string to parse.
    std::stringstream input_;
  };

  /// Display the content of the tweast.
  std::ostream& operator<< (std::ostream& ostr, const Tweast& in);

}

# include <parse/tweast.hxx>

#endif // !PARSE_TWEAST_HH
