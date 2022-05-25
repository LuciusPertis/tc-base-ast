/**
 ** \file assem/instr.cc
 ** \brief Implementation of the root of assembly instructions.
 */

#include <ostream>

#include <assem/instr.hh>
#include <misc/contract.hh>
#include <temp/temp.hh>

namespace assem
{
  // The slot to store the current indentation level.
  const misc::xalloc<bool> Instr::debug;

  std::ostream& Instr::dump(std::ostream& ostr) const
  {
    auto dst_iter = def().begin();
    auto src_iter = use().begin();
    auto lab_iter = jumps().begin();

    for (unsigned i = 0; i < assem_.size(); ++i)
      if (assem_[i] == '\'')
        switch (assem_[++i])
          {
          case 's':
            assertion(src_iter != use().end());
            ostr << *src_iter;
            ++src_iter;
            break;
          case 'd':
            assertion(dst_iter != def().end());
            ostr << *dst_iter;
            ++dst_iter;
            break;
          case 'j':
            assertion(lab_iter != jumps().end());
            ostr << lab_iter->string_get();
            ++lab_iter;
            break;
          default:
            // Never reached.
            unreachable();
          }
      else
        ostr << assem_[i];

    // Be sure to output the transformed names.
    if (debug(ostr))
      {
        ostr << "\t#";
        if (!def().empty())
          ostr << " def: " << def();
        if (!use().empty())
          ostr << " use: " << use();
        if (!jumps().empty())
          ostr << " jmp: " << jumps();
      }

    return ostr;
  }

} // namespace assem
