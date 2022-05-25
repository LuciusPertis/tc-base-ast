/**
 ** \file assem/label.hxx
 ** \brief Specialization of assem::Instr for labels.
 */

#pragma once

#include <assem/label.hh>

namespace assem
{
  inline Label::Label(const std::string& assem, const temp::Label& label)
    : Instr(assem)
    , label_(label)
  {}

  inline temp::Label Label::label_get() const { return label_; }

} // namespace assem
