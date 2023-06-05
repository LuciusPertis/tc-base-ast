/**
 ** \file target/cpu.hh
 ** \brief Declaration of target::Cpu.
 */

#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <temp/fwd.hh>

namespace target
{
  /// A Cpu mainly describes target machine's registers.
  class Cpu
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Cpu (default).
    Cpu();
    /// Destroy a Cpu.
    virtual ~Cpu() = default;
    /** \} */

    /** \name Descriptors of this architecture.
     ** \{ */
  public:
    /// The byte size of a memory's word.
    virtual size_t word_size_get() const = 0;

    /// The number of registers.
    virtual size_t nb_regs() const;

    /// The frame pointer register.
    virtual const temp::Temp& fp_reg() const = 0;

    /// The result register.
    virtual const temp::Temp& result_reg() const = 0;

    /// Mapping from tc pseudos to hard registers.
    virtual const temp::TempMap& tempmap_get() const;

    /// Arguments-dedicated registers.
    virtual const temp::temp_list_type& argument_regs() const;

    /// Caller save registers.
    virtual const temp::temp_set_type& caller_save_regs() const;

    /// Callee save registers.
    virtual const temp::temp_set_type& callee_save_regs() const;

    /// Special registers (e.g., $fp, $sp, $zero etc.).
    virtual const temp::temp_set_type& special_regs() const;

    /// The whole register set.
    virtual temp::temp_set_type registers_get() const;
    /** \} */

    /** \name Register registers.
     ** \{ */
  protected:
    /// Argument dedicated register.
    virtual void argument_reg(const std::string& name);

    /// Argument dedicated register.
    virtual void argument_reg(std::initializer_list<std::string> names);

    /// Caller save register.
    virtual void caller_save_reg(const std::string& name);

    /// Caller save registers.
    virtual void caller_save_reg(std::initializer_list<std::string> names);

    /// Callee save register.
    virtual void callee_save_reg(const std::string& name);

    /// Callee save registers.
    virtual void callee_save_reg(std::initializer_list<std::string> names);

    /// Special registers, unavailable for register allocaction.
    virtual void special_reg(const temp::Temp& t);

    /// Special registers, unavailable for register allocaction.
    virtual void special_reg(std::initializer_list<temp::Temp> temp_list);
    /** \} */

    /** \name Register classes.
     ** \{ */
  protected:
    /// Callee save registers.
    temp::temp_set_type callee_save_registers_;

    /// Caller save registers
    temp::temp_set_type caller_save_registers_;

    /// Argument registers.
    temp::temp_list_type argument_registers_;

    /// Remaining registers.
    temp::temp_set_type special_registers_;

    /// Mapping from pseudos to hard registers.
    std::unique_ptr<temp::TempMap> tempmap_;
    /** \} */

  public:
    /// Describing a CPU.
    std::ostream& dump(std::ostream& ostr) const;
  };

  /// Output \a cpu on \a ostr.
  std::ostream& operator<<(std::ostream& ostr, const Cpu& cpu);

} // namespace target
