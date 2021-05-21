/**
 ** \file assem/fragment.cc
 ** \brief Fragments of assembly.
 */

#include <string>

#include <assem/fragment.hh>
#include <assem/fragments.hh>
#include <assem/visitor.hh>
#include <misc/escape.hh>
#include <temp/label.hh>

namespace assem
{
  /*-----------.
  | DataFrag.  |
  `-----------*/

  void DataFrag::accept(Visitor& v) { v(*this); }

  void DataFrag::accept(ConstVisitor& v) const { v(*this); }

  std::ostream& DataFrag::dump(std::ostream& ostr) const
  {
    ostr << ".data\n"
         << data_frag_.label_get() << ":\n"
         << "\t.word " << data_frag_.data_get().length() << '\n'
         << "\t.asciiz \"" << misc::escape(data_frag_.data_get()) << "\"\n"
         << ".text\n";
    return ostr;
  }

  /*-----------.
  | ProcFrag.  |
  `-----------*/

  void ProcFrag::accept(Visitor& v) { v(*this); }

  void ProcFrag::accept(ConstVisitor& v) const { v(*this); }

  std::string ProcFrag::file_name(const std::string& p,
                                  const std::string& s) const
  {
    return (p == "" ? "" : (p + ".")) + label_.string_get() + "." + name_.get()
      + (s == "" ? "" : ("." + s));
  }

  std::ostream& ProcFrag::dump(std::ostream& ostr) const
  {
    return ostr << "# Routine: " << name_ << '\n' << instrs_ << std::endl;
  }

} // namespace assem
