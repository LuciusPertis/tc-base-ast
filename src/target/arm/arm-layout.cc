/**
 ** \file target/ia32/gas-layout.cc
 ** \brief Print assembly for ARM
 */

#include <assem/libassem.hh>
#include <misc/contract.hh>
#include <misc/escape.hh>
#include <target/arm/arm-layout.hh>
#include <temp/label.hh>
#include <tree/all.hh>

namespace target::arm
{
  ArmLayout& ArmLayout::instance()
  {
    static ArmLayout unique;
    return unique;
  }

  void ArmLayout::operator()(const assem::DataFrag& data_frag)
  {
    precondition(postr_);
    const tree::DataFrag& data = data_frag.data_get();

    *postr_ << ".data\n"
            << data.label_get() << ":\n"
            << "\t.word " << data.data_get().length() << "\n"
            << "\t.asciz \"" << misc::escape(data.data_get()) << "\"\n";
  }

  void ArmLayout::operator()(const assem::ProcFrag& proc_frag)
  {
    precondition(postr_);
    std::string routine_label = "tc_" + proc_frag.label_get().string_get();
    temp::Label routine_end;

    *postr_ << "# Routine: " << proc_frag.name_get() << "\n"
            << ".global " << routine_label << "\n"
            << ".text\n"
            << proc_frag.instrs_get() << "\n"
            << ".ltorg\n";
  }

  void ArmLayout::operator()(const assem::Fragments& frags)
  {
    precondition(postr_);

    *postr_ << "# Tiger final assembler ouput.\n\n";

    Layout::operator()(frags);
  }
} // namespace target::arm
