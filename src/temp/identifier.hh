/**
 ** \file temp/identifier.hh
 ** \brief Fresh temporaries.
 */

#ifndef TEMP_IDENTIFIER_HH
# define TEMP_IDENTIFIER_HH

# include <iosfwd>
# include <string>

# include <boost/variant/variant.hpp>

# include <misc/symbol.hh>
# include <misc/xalloc.hh>
# include <temp/fwd.hh>

namespace temp
{

  /*-------------.
  | Identifier.  |
  `-------------*/

  /** \brief Root for Named or anonymous (fresh) identifiers.

  It is used to factor the implementation of temp::Temp and
  temp::Label.

  \param Traits  a traits that should have two members:
  the string \a prefix and the integer rank.

  This class template makes it possible to instantiate several natures
  of identifiers, say identifiers tagged with an int, a
  misc::symbol, and so forth.  Identifiers uses a boost::variant to
  store its actual value. Currently, this variant can hold an unsigned
  or a misc::symbol.

  We need a total order on Identifier, so first we need a
  comparison on identifier of same value type (i.e., an order
  on int, an order on misc::symbol etc.), but we also need
  an order between identifiers of different kinds: int versus
  misc::symbol etc.

  To implement this, Traits\<Tag_\>::rank must return a unique
  int which will serve to compare heterogeneous identifiers.
  For instance if

  \code
  Traits<int>::rank < Traits<misc::symbol>::rank
  \endcode

  then a numbered Identifier will be sorted before a named
  Identifier.

  We also need to know how to print an Identifier.  For instance,
  numbered temporaries are reported as \a t42, while the temp
  named \a $fp is to be printed as is.  The value of
  Traits_\<Tag_ \>::prefix will be printed before the value
  of the tag itself.  Hence, to print \a t42, specify

  \code
  const std::string temp_traits<int> prefix = "t";
  \endcode
  */

  template <template <typename Tag_> class Traits_>
  class Identifier
  {
  public:
    typedef Identifier<Traits_> self_type;
    /// Type of the ``content'' of the identifier.
    typedef boost::variant<unsigned, misc::symbol> value_type;

  public:
    Identifier();
    Identifier(const misc::symbol& sym);
    Identifier(const std::string& str);
    Identifier(const char* str);
    Identifier(const self_type& id);

  public:
    std::ostream& dump(std::ostream&) const;
    /// Same as dump, but return a string.
    std::string string_get() const;
    const value_type& value_get() const;
    const std::string& prefix_get() const;
    int rank_get() const;

  public:
    self_type& operator=(const self_type& rhs);

    bool operator==(const self_type& rhs) const;
    bool operator!=(const self_type& rhs) const;
    bool operator<(const self_type& rhs) const;
    bool operator<=(const self_type& rhs) const;
    bool operator>(const self_type& rhs) const;
    bool operator>=(const self_type& rhs) const;

  public:
    /// Identifier filter type.
    typedef misc::endo_map<Identifier> map_type;
    /// Filtering identifier outputs.
    static const misc::xalloc<map_type*> map;

  private:
    value_type value_;
    const std::string* prefix_;
    int rank_;

  private:
    /// Unique counter for this kind of identifier.
    static unsigned count_;
  };

  /// Print \a i on \a o.
  template <template <typename Tag_> class Traits_>
  std::ostream& operator<<(std::ostream& o, const Identifier<Traits_>& i);


  /*------------------.
  | Variant visitor.  |
  `------------------*/

  template <template <typename Elt_> class Cmp_>
  class IdentifierCompareVisitor : public boost::static_visitor<bool>
  {
  public:
    template <typename T, typename U>
    bool operator()(const T&, const U&) const;

    template <typename T>
    bool operator()(const T& lhs, const T& rhs) const;
  };

  typedef IdentifierCompareVisitor<std::equal_to> IdentifierEqualToVisitor;
  typedef IdentifierCompareVisitor<std::less> IdentifierLessThanVisitor;

} // namespace temp

# include <temp/identifier.hxx>

#endif // !TEMP_IDENTIFIER_HH
