/**
 ** \file assem/fragments.cc
 ** \brief Implementation of assem::Fragments.
 */

#include <functional>

#include <assem/fragment.hh>
#include <assem/fragments.hh>
#include <misc/algorithm.hh>
#include <misc/contract.hh>

namespace assem
{
  Fragments::~Fragments() { misc::deep_clear(*this); }

  std::ostream& Fragments::print(std::ostream& ostr)
  {
    ostr << "# == Final assembler ouput. == #\n";

    for (const Fragment* frag : *this)
      {
        invariant(frag != nullptr);
        ostr << *frag << '\n';
      }
    ostr << std::flush;
    return ostr;
  }

} // namespace assem
