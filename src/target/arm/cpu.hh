/**
 ** \file target/arm/cpu.hh
 ** \brief Define ARM CPU.
 */

#pragma once

#include <target/cpu.hh>

namespace target::arm
{
  /// Describes ARM-32's registers.
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

    /// Link register
    virtual const temp::Temp& lr_reg() const;

    /// Result register.
    const temp::Temp& result_reg() const override;
  };
} // namespace target::arm
