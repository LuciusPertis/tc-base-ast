/**
 ** \file assem/oper.hxx
 ** \brief Implementation for assem/oper.hh.
 */
#pragma once

#include <ostream>

#include <assem/oper.hh>

namespace assem
{
  inline Oper::Oper(const std::string& assem,
                    const temp::temp_list_type& used_temps,
                    const temp::temp_list_type& defd_temps,
                    const temp::label_list_type& jump_labels)
    : Instr(assem, used_temps, defd_temps, jump_labels)
  {}

  inline std::ostream& Oper::dump(std::ostream& ostr) const
  {
    ostr << '\t';
    return Instr::dump(ostr);
  }

} // namespace assem
