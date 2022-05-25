/**
 ** \file target/mips/target.hh
 ** \brief Define the MIPS Target.
 */

#pragma once

#include <target/mips/cpu.hh>
#include <target/mips/spim-assembly.hh>
#include <target/mips/spim-codegen.hh>
#include <target/target.hh>

namespace target::mips
{
  /// A MIPS Target is the union of a MIPS Cpu and a MIPS Codegen.
  class Target : public target::Target
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Build a Target.
    Target(const CpuLimits& limits, bool rule_trace_p = false);
    /** \} */

    const Cpu& cpu_get() const override;
    Cpu& cpu_get() override;

    const Assembly& assembly_get() const override;
    Assembly& assembly_get() override;

    const SpimCodegen& codegen_get() const override;
    SpimCodegen& codegen_get() override;

  protected:
    mips::Cpu cpu_;

    mips::SpimCodegen codegen_;

    // This should be a target::mips::Assembly, dynamicaly set to
    // SpimAssembly or other.
    mips::SpimAssembly assembly_;
  };
} // namespace target::mips
