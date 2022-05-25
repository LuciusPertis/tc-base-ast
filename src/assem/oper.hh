/**
 ** \file assem/oper.hh
 ** \brief Specialization of assem::Instr for general operators.
 */

#pragma once

#include <assem/instr.hh>

namespace assem
{
  class Oper : public Instr
  {
  public:
    Oper(const std::string& assem,
         const temp::temp_list_type& used_temps,
         const temp::temp_list_type& defd_temps,
         const temp::label_list_type& jump_labels = temp::label_list_type());

    std::ostream& dump(std::ostream& ostr) const override;
  }; // class Oper

} // namespace assem

#include <assem/oper.hxx>
