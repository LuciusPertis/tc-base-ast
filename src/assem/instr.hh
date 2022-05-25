/**
 ** \file assem/instr.hh
 ** \brief Root of assembly instructions implementation.
 */

#pragma once

#include <iosfwd>
#include <string>

#include <misc/xalloc.hh>
#include <temp/fwd.hh>
#include <temp/temp.hh>

namespace assem
{
  /** \brief Root for abstract assembly instructions.

     Assemly instructions are composed of a string (the instruction
     itself) a` la printf, where

     - "'s" designates a source register

     - "'d" designates a destination register

     - "'j" designates a destination (jump) label

     and of three lists

     - source registers

     - destination registers

     - destination labels

     After instruction selection, the registers are mostly soft (or
     pseudo) registers, and register allocation replaces then with
     hard registers. */
  class Instr
  {
  public:
    Instr(const std::string& assem,
          const temp::temp_list_type& used_temps = temp::temp_list_type(),
          const temp::temp_list_type& defd_temps = temp::temp_list_type(),
          const temp::label_list_type& jump_labels = temp::label_list_type());

    virtual ~Instr() = default;

    const temp::temp_list_type& use() const;
    const temp::temp_list_type& def() const;
    const temp::label_list_type& jumps() const;

    temp::temp_list_type& use();
    temp::temp_list_type& def();

    /// Output the TempMap \a m onto \a ostr.
    virtual std::ostream& dump(std::ostream& ostr) const;

    /** \brief Set whether Instr::print report debugging information?
        Return the previous value.  */
    static const misc::xalloc<bool> debug;

  protected:
    std::string assem_;
    temp::temp_list_type use_;
    temp::temp_list_type def_;
    temp::label_list_type jumps_;
  }; // class Instr

  inline std::ostream& operator<<(std::ostream& ostr, const Instr& instr);

} // namespace assem

#include <assem/instr.hxx>
