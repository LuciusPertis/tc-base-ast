/**
 ** \file assem/instr.cc
 ** \brief Implementation of the root of assembly instructions.
 */

#include <ostream>
#include <misc/contract.hh>
#include <assem/instr.hh>
#include <temp/temp.hh>

namespace assem
{
  Instr::~Instr()
  {}

  // The slot to store the current indentation level.
  const misc::xalloc<bool> Instr::debug;

  std::ostream&
  Instr::dump(std::ostream& ostr) const
  {
    temp::temp_list_type::const_iterator dst_iter = def().begin();
    temp::temp_list_type::const_iterator src_iter = use().begin();
    temp::label_list_type::const_iterator lab_iter = jumps().begin();

    for (unsigned i = 0; i < assem_.size(); ++i)
      if (assem_[i] == '\'')
        switch (assem_[++i])
          {
          case 's' :
            assertion(src_iter != use().end());
            ostr << *src_iter++;
            break;
          case 'd' :
            assertion(dst_iter != def().end());
            ostr << *dst_iter++;
            break;
          case 'j' :
            assertion(lab_iter != jumps().end());
            ostr << (lab_iter++)->string_get();
            break;
          default :
            // Never reached.
            unreached();
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
