/**
 ** \file astclone/cloner.hxx
 ** \brief Template methods of astclone::Cloner.
 */

#ifndef ASTCLONE_CLONER_HXX
# define ASTCLONE_CLONER_HXX

# include <ast/libast.hh>
# include <astclone/cloner.hh>

namespace astclone
{
  using namespace ast;

  template <typename T>
  T*
  Cloner::recurse(const T& t)
  {
    t.accept(*this);
    T* res = dynamic_cast<T*>(result_);
    assertion(res);
    return res;
  }

  template <typename T>
  T*
  Cloner::recurse(const T* const t)
  {
    T* res = nullptr;
    if (t)
      {
        t->accept(*this);
        res = dynamic_cast<T*>(result_);
        assertion(res);
      }
    return res;
  }

  template <typename CollectionType>
  CollectionType*
  Cloner::recurse_collection(const CollectionType& c)
  {
    auto res = new CollectionType;

    typedef typename CollectionType::value_type elt_type;
    for (const elt_type& e : c)
      {
        e->accept(*this);
        auto elt = dynamic_cast<elt_type>(result_);
        assertion(elt);
        res->push_back(elt);
      }

    return res;
  }

  template <typename DecsType>
  void
  Cloner::decs_visit(const DecsType& e)
  {
    const Location& location = e.location_get();

    // Shorthand.
    typedef DecsType decs_type;
    // The type of the list contained by this node.
    typedef typename decs_type::Ds elt_type;
    // The cloned list of declarations.
    auto decs = new elt_type;

    for (const typename elt_type::value_type& i : e.decs_get())
      {
        i->accept(*this);
        auto dec = dynamic_cast <typename elt_type::value_type>(result_);
        assertion(dec);
        decs->push_back(dec);
      }
    // The cloned Decs.
    result_ = new decs_type(location, decs);
  }

} // namespace astclone

#endif // !ASTCLONE_CLONER_HXX
