/**
 ** \file target/mips/spim-layout.cc
 ** \brief Abstract a fragment's layout.
 */

#include <assem/libassem.hh>
#include <misc/contract.hh>
#include <misc/escape.hh>
#include <target/mips/spim-layout.hh>
#include <tree/all.hh>

namespace target::mips
{
  SpimLayout& SpimLayout::instance()
  {
    static SpimLayout unique;
    return unique;
  }

  void SpimLayout::operator()(const assem::DataFrag& data_frag)
  {
    precondition(postr_);
    const tree::DataFrag& data = data_frag.data_get();
    *postr_ << ".data\n"
            << data.label_get() << ":\n"
            << "\t.word " << data.data_get().length() << "\n"
            << "\t.asciiz \"" << misc::escape(data.data_get()) << "\"\n"
            << ".text\n";
  }

  void SpimLayout::operator()(const assem::ProcFrag& proc_frag)
  {
    precondition(postr_);
    *postr_ << "# Routine: " << proc_frag.name_get() << "\n"
            << proc_frag.instrs_get();
  }

  void SpimLayout::operator()(const assem::Fragments& frags)
  {
    precondition(postr_);
    *postr_ << "# == Final assembler ouput. == #\n";
    Layout::operator()(frags);
  }
} // namespace target::mips
