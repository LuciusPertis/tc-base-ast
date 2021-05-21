/**
 ** \file target/ia32/gas-layout.cc
 ** \brief Print assembly for IA-32 a la GAS
 */

#include <assem/libassem.hh>
#include <misc/contract.hh>
#include <misc/escape.hh>
#include <target/ia32/gas-layout.hh>
#include <temp/label.hh>
#include <tree/all.hh>

namespace target::ia32
{
  GasLayout& GasLayout::instance()
  {
    static GasLayout unique;
    return unique;
  }

  void GasLayout::operator()(const assem::DataFrag& data_frag)
  {
    precondition(postr_);
    const tree::DataFrag& data = data_frag.data_get();
    *postr_ << "\t.section\t.rodata\n"
            << data.label_get() << ":\n"
            << "\t.long " << data.data_get().length() << "\n"
            << "\t.asciz \"" << misc::escape(data.data_get()) << "\"\n";
  }

  void GasLayout::operator()(const assem::ProcFrag& proc_frag)
  {
    precondition(postr_);
    std::string routine_label = "tc_" + proc_frag.label_get().string_get();
    temp::Label routine_end;

    *postr_ << "/** Routine: " << proc_frag.name_get() << " */\n"
            << "\t.text\n"
            << "\t.globl\t" << routine_label << "\n"
            << "\t.type\t" << routine_label << ",@function\n"
            << proc_frag.instrs_get() << routine_end << ":\n"
            << "\t.size\t" << routine_label << ',' << routine_end << '-'
            << routine_label << "\n";
  }

  void GasLayout::operator()(const assem::Fragments& frags)
  {
    precondition(postr_);

    *postr_ << "/** Tiger final assembler ouput. */\n"
            << "\n";
    Layout::operator()(frags);
    *postr_ << "\t.ident\t\"LRDE Tiger Compiler\"\n";
  }
} // namespace target::ia32
