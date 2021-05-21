/**
 ** \file assem/label.hh
 ** \brief Specialization of assem::Instr for labels.
 */

#pragma once

#include <assem/instr.hh>
#include <temp/label.hh>

namespace assem
{
  class Label : public Instr
  {
  public:
    Label(const std::string& assem, const temp::Label& label);

    temp::Label label_get() const;

  private:
    temp::Label label_;
  }; // class Label

} // namespace assem

#include <assem/label.hxx>
