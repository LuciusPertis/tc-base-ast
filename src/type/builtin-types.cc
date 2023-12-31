/**
 ** \file type/builtin-types.cc
 ** \brief Implementation for type/builtin-types.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/record.hh>
#include <type/class.hh>

namespace type
{
  /*------.
  | Nil.  |
  `------*/

  const Nil&
  Nil::instance()
  {
    static Nil the_;
    return the_;
  }

  std::ostream&
  Nil::dump(std::ostream& ostr) const
  {
    return ostr << "nil";
  }


  // FIXME: Some code was deleted here (Void, Int, and String).

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Nil).

} // namespace type
