/**
 ** \file assem/instrs.cc
 ** \brief Implementation of assem::Instrs.
 */

#include <algorithm>
#include <assem/instr.hh>
#include <assem/instrs.hh>
#include <assem/label.hh>
#include <misc/algorithm.hh>

namespace assem
{
  Instrs::Instrs(std::initializer_list<Instr*> l)
  {
    insert(begin(), l.begin(), l.end());
  }

  Instrs::~Instrs()
  {
    /* As assem::Instrs is not copyable, the assem::Instr (with no
       `s') objects stored in the list (as pointers) are not shared
       among several instances of this class.  Therefore, as long as
       instr::Instrs has ownership of the list's elements, we can
       safely dispose of these objects when this assem::Instrs object
       gets destroyed.  */
    misc::deep_clear(*this);
  }

  Instrs::iterator Instrs::label_find(const temp::Label& l)
  {
    return std::ranges::find_if(*this, [&l](Instr* i) -> bool {
      auto* li = dynamic_cast<Label*>(i);
      return (li && li->label_get() == l);
    });
  }

  std::ostream& Instrs::dump(std::ostream& ostr) const
  {
    for (const Instr* instr : *this)
      {
        assertion(instr);
        ostr << *instr << '\n';
      }
    ostr << std::flush;

    return ostr;
  }

  std::ostream& operator<<(std::ostream& ostr, const Instrs& instrs)
  {
    return instrs.dump(ostr);
  }

} // namespace assem
