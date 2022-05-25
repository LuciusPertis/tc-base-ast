/**
 ** \file target/ia32/cpu.hh
 ** \brief Define IA32 CPU.
 */

#pragma once

#include <target/cpu.hh>

namespace target::ia32
{
  /// Describes IA-32's registers.
  class Cpu : public target::Cpu
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Cpu (default).
    Cpu();
    /** \} */

    /// Word size.
    size_t word_size_get() const override;

    /// Frame pointer.
    const temp::Temp& fp_reg() const override;

    /// Stack pointer.
    virtual const temp::Temp& sp_reg() const;

    /// Result register.
    const temp::Temp& result_reg() const override;
  };
} // namespace target::ia32
