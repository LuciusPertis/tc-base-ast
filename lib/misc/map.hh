/**
 ** \file misc/map.hh
 ** \brief Declaration of misc::Map.
 */

#ifndef MISC_MAP_HH
# define MISC_MAP_HH

# include <list>
# include <map>
# include <stdexcept>

namespace misc
{
  /** \brief Wrapper around std::map providing syntactic sugar
      for any mapping of types manipulation. */
  template <class T, class N>
  class map
  {
  protected:
    typedef std::map<T, N> map_type;

  public:
    /// The map's key type.
    typedef typename map_type::key_type key_type;
    /// The type of object associated with the keys.
    typedef typename map_type::mapped_type mapped_type;
    /// The type of object, std::pair<const key_type, data_type>,
    /// stored in the map.
    typedef typename map_type::value_type value_type;
    /// Type of the function object that compares two keys for ordering.
    typedef typename map_type::key_compare key_compare;
    /// Iterator used to iterate through a map.
    typedef typename map_type::iterator iterator;
    /// Const iterator used to iterate through a map.
    typedef typename map_type::const_iterator const_iterator;

  public:
    /// \name Constructors and destructor.
    /// \{
    map();
    /// Return a duplicate of \a this.
    virtual ~map();
    /// \}

    /// Return a duplicate of \a this.
    virtual map* clone() const;

    /// Returns the key_compare object used by the map.
    key_compare key_comp() const;

    /// Lookup for \a t.
    /// \{
    virtual iterator       find(const T& t);
    virtual const_iterator find(const T& t) const;
    /// \}

    /// Lookup for \a t and throw an exception if not available.
    /// \{
    virtual iterator       xfind(const T& t);
    virtual const_iterator xfind(const T& t) const;
    /// \}

    /// Lookup for the value associated to \a t.
    virtual N operator[](const T& t) const;

    /// \brief Return a reference to the value associated to \a t.
    ///
    /// This method is not virtual, so that it is not automatically
    /// instantiated at the instantiation of misc::map.  This way,
    /// there won't be errors from the compiler about \a N not being a
    /// model of the concept Default Constructible.  This is needed
    /// for some instantiations of misc::map, notably the ones that
    /// uses a symbol::Symbol as mapped type, which has no default
    /// constructor (note that in this case everything will be fine as
    /// long as this method is not called -- compile errors will occur
    /// otherwise).
    ///
    /// We might want to provide two flavors of misc::map, one that
    /// requires that its second parameter is a model of Default
    /// Constructible and that provides an operator[] similar to
    /// std::map's; and another one that doesn't.
    N& operator[](const T& t);

    /// Lookup for \a t, throwing std::range_error if it is not found.
    virtual N operator()(const T& t) const;

    /// Lookup for a list \a ts of T's, throwing std::range_error if
    /// one or several elements are not found.
    virtual std::list<N>
    operator()(const std::list<T>& ts) const;

    /// \name Iterating.
    /// \{
    virtual iterator       begin();
    virtual iterator       end();
    virtual const_iterator begin() const;
    virtual const_iterator end() const;
    /// \}

    /// Finds the first element whose key is not less than \a k.
    /// \{
    virtual iterator lower_bound(const T& k);
    virtual const_iterator lower_bound(const T& k) const;
    /// \}

    /// Inserts \a x into the map.
    virtual std::pair<iterator, bool> insert(const std::pair<const T, N>& x);
    /// Copy the contents of \a other to \a this.
    virtual void insert(const map& other);

    /// Insert a new element built in-place using \a args into the map.
    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    /// Is the map empty ?
    virtual bool empty() const;

    /// Number of known identifiers.
    virtual size_t size() const;

    /// Remove and return mapping for \a t from the map.
    virtual N take(const T& t);

    /// Erase all of the elements.
    virtual void clear();

    /// Description of known mappings.
    virtual std::ostream& print(std::ostream& ostr) const;

  protected:
    /// Mapping from T to N.
    map_type map_;
  };


  /// Output \a m onto \a ostr.
  template <class T, class N>
  std::ostream& operator<<(std::ostream& ostr, const map<T, N>& m);
}

# include <misc/map.hxx>

#endif // !MISC_MAP_HH
