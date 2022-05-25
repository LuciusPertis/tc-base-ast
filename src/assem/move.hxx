/**
 ** \file assem/move.hxx
 ** \brief Inline methods for assem/move.hh.
 */

#pragma once

#include <assem/move.hh>
#include <misc/contract.hh>

namespace assem
{
  using L = temp::temp_list_type;

  inline Move::Move(const std::string& assem,
                    const temp::Temp& used_temps,
                    const temp::Temp& defd_temps)
    : Instr(assem, L(used_temps), L(defd_temps))
  {}

  inline temp::Temp Move::dst_get() const { return def().front(); }

  inline temp::Temp Move::src_get() const { return use().front(); }

  inline temp::Temp Move::use_get() const
  {
    precondition(use_.size() == 1);
    return use_.front();
  }

  inline temp::Temp Move::def_get() const
  {
    precondition(def_.size() == 1);
    return def_.front();
  }

  inline std::ostream& Move::dump(std::ostream& ostr) const
  {
    ostr << '\t';
    return Instr::dump(ostr);
  }

} // namespace assem
