/**
 ** \file misc/variant.hxx
 ** \brief Implementation of misc::variant.
 **/

#ifndef MISC_VARIANT_HXX
# define MISC_VARIANT_HXX

# include <type_traits>
# include <boost/variant/get.hpp>
# include <misc/variant.hh>

namespace misc
{

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::variant(const U& rhs)
    : super_type(rhs)
  {}

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>&
  variant<T, Ts...>::operator=(const U& rhs)
  {
    // Don't assign to oneself.
    if (static_cast<const void*>(&rhs) != static_cast<const void*>(this))
      super_type::operator=(rhs);
    return *this;
  }


  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::operator U& ()
  {
    return boost::get<U>(*this);
  }

  template <typename T, typename... Ts>
  template <typename U>
  variant<T, Ts...>::operator const U& () const
  {
  // FIXME: Some code was deleted here.
  }

} // namespace misc

#endif // !MISC_VARIANT_HXX
