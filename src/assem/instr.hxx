/**
 ** \file assem/instr.hxx
 ** \brief Root of assembly instructions implementation.
 */

#pragma once

#include <assem/instr.hh>

namespace assem
{
  inline Instr::Instr(const std::string& assem,
                      const temp::temp_list_type& used_temps,
                      const temp::temp_list_type& defd_temps,
                      const temp::label_list_type& jump_labels)
    : assem_(assem)
    , use_(used_temps)
    , def_(defd_temps)
    , jumps_(jump_labels)
  {}

  inline const temp::temp_list_type& Instr::use() const { return use_; }

  inline temp::temp_list_type& Instr::use() { return use_; }

  inline const temp::temp_list_type& Instr::def() const { return def_; }

  inline temp::temp_list_type& Instr::def() { return def_; }

  inline const temp::label_list_type& Instr::jumps() const { return jumps_; }

  inline std::ostream& operator<<(std::ostream& ostr, const Instr& instr)
  {
    return instr.dump(ostr);
  }

} // namespace assem
