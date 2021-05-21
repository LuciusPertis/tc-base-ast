/**
 ** \file assem/fragments.hh
 ** \brief Fragments of assembly.
 */

#pragma once

#include <vector>

#include <assem/fwd.hh>

namespace assem
{
  /// Abstract a fragment in assembly language.
  class Fragments : public std::vector<Fragment*>
  {
  public:
    /// Destroy all the fragments, and reclaim the whole memory.
    virtual ~Fragments();

    /// \brief Issue the \a fragments on \a ostr.
    std::ostream& print(std::ostream& ostr);
  };

  std::ostream& operator<<(std::ostream& ostr, const Fragments& fragments);

} // namespace assem
