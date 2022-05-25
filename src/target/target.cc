/**
 ** \file target/target.cc
 ** \brief Abstract a Target machine.
 */

#include <target/cpu.hh>
#include <target/target.hh>

namespace target
{
  std::ostream& Target::dump(std::ostream& ostr) const
  {
    return ostr << cpu_get();
  }

  std::ostream& operator<<(std::ostream& ostr, const Target& t)
  {
    return t.dump(ostr);
  }

} // namespace target
