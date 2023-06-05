/**
 ** \file assem/layout.cc
 ** \brief Implementation for assem/layout.hh.
 */

#include <assem/fragment.hh>
#include <assem/fragments.hh>
#include <assem/layout.hh>

namespace assem
{
  void Layout::operator()(const Fragments& frags)
  {
    precondition(postr_);
    for (auto i = frags.begin(); i != frags.end(); ++i)
      {
        if (i != frags.begin())
          *postr_ << '\n';
        invariant(*i);
        (*i)->accept(*this);
      }
    *postr_ << std::flush;
  }

} // namespace assem
