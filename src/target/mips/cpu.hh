/**
 ** \file target/mips/cpu.hh
 ** \brief Define the MIPS CPU.
 */

#pragma once

#include <target/cpu.hh>
#include <target/fwd.hh>

namespace target::mips
{
  /// Describes MIPS's registers.
  class Cpu : public target::Cpu
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Cpu.
    Cpu(const CpuLimits& limits);
    /** \} */

    size_t word_size_get() const override;

    /// Frame pointer.
    const temp::Temp& fp_reg() const override;

    /// Stack pointer.
    virtual const temp::Temp& sp_reg() const;

    /// Result register
    const temp::Temp& result_reg() const override;

    /// Return address
    virtual const temp::Temp& return_reg() const;

    /// Special register containing constant 0.
    const temp::Temp& zero_reg() const;
  };
} // namespace target::mips
