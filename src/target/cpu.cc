/**
 ** \file target/cpu.cc
 ** \brief Implementation of target::Cpu.
 */

#include <iostream>

#include <misc/algorithm.hh>
#include <misc/indent.hh>
#include <target/cpu.hh>
#include <temp/temp-set.hh>
#include <temp/temp.hh>

namespace target
{
  Cpu::Cpu()
    : tempmap_(new temp::Temp::map_type)
  {}

  temp::temp_set_type Cpu::registers_get() const
  {
    temp::temp_set_type res =
      (callee_save_registers_ | caller_save_registers_ | special_registers_);
    for (const temp::Temp& t : argument_registers_)
      res += t;
    return res;
  }

  size_t Cpu::nb_regs() const
  {
    static const size_t nb_regs_ =
      (callee_save_registers_.size() + caller_save_registers_.size()
       + argument_registers_.size() + special_registers_.size());
    return nb_regs_;
  }

  // Mapping from tc pseudos to hard registers.
  const temp::TempMap& Cpu::tempmap_get() const { return *tempmap_; }

  // Describing a CPU.
  std::ostream& Cpu::dump(std::ostream& ostr) const
  {
#define REGS_PRINT(Name, Regs)                                                 \
  ostr << (Name) << " (" << (Regs).size() << "): " << (Regs) << '\n'

    ostr << "CPU (" << nb_regs() << ")\n";
    REGS_PRINT("Arguments  ", argument_registers_);
    REGS_PRINT("Caller Save", caller_save_registers_);
    REGS_PRINT("Callee Save", callee_save_registers_);
    REGS_PRINT("Special    ", special_registers_);

#undef REGS_PRINT
    ostr << "TempMap" << misc::incendl << *tempmap_ << misc::decendl;

    return ostr;
  }

  const temp::temp_list_type& Cpu::argument_regs() const
  {
    return argument_registers_;
  }

  const temp::temp_set_type& Cpu::caller_save_regs() const
  {
    return caller_save_registers_;
  }

  const temp::temp_set_type& Cpu::callee_save_regs() const
  {
    return callee_save_registers_;
  }

  const temp::temp_set_type& Cpu::special_regs() const
  {
    return special_registers_;
  }

  void Cpu::argument_reg(const std::string& name)
  {
    temp::Temp t(name);
    argument_registers_.emplace_back(t);
  }

  void Cpu::argument_reg(std::initializer_list<std::string> names)
  {
    for (auto name : names)
      {
        temp::Temp t(name);
        argument_registers_.emplace_back(t);
      }
  }

  void Cpu::caller_save_reg(const std::string& name)
  {
    temp::Temp t(name);
    caller_save_registers_.insert(t);
  }

  void Cpu::caller_save_reg(std::initializer_list<std::string> names)
  {
    for (auto name : names)
      {
        temp::Temp t(name);
        caller_save_registers_.insert(t);
      }
  }

  void Cpu::callee_save_reg(const std::string& name)
  {
    temp::Temp t(name);
    callee_save_registers_.insert(t);
  }

  void Cpu::callee_save_reg(std::initializer_list<std::string> names)
  {
    for (auto name : names)
      {
        temp::Temp t(name);
        callee_save_registers_.insert(t);
      }
  }

  void Cpu::special_reg(const temp::Temp& t) { special_registers_.insert(t); }

  void Cpu::special_reg(std::initializer_list<temp::Temp> temp_list)
  {
    special_registers_.insert(temp_list.begin(), temp_list.end());
  }

  std::ostream& operator<<(std::ostream& ostr, const Cpu& cpu)
  {
    return cpu.dump(ostr);
  }

} // namespace target
