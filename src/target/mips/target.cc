/**
 ** \file target/mips/target.cc
 ** \brief Define the mips::Target.
 */

#include <target/mips/target.hh>
#include <target/mips/spim-assembly.hh>
#include <target/mips/codegen.hh>
#include <target/mips/cpu.hh>
#include <target/tasks.hh>

namespace target
{
  namespace mips
  {

    Target::Target(const CpuLimits& limits, bool rule_trace_p)
      : cpu_(limits)
      , codegen_(rule_trace_p)
    {
      codegen_.cpu_set(cpu_);
      codegen_.assembly_set(assembly_);
    }

    Target::~Target()
    {
    }

    const Cpu&
    Target::cpu_get() const
    {
      return cpu_;
    }

    Cpu&
    Target::cpu_get()
    {
      return cpu_;
    }

    const Assembly&
    Target::assembly_get() const
    {
      return assembly_;
    }

    Assembly&
    Target::assembly_get()
    {
      return assembly_;
    }

    const Codegen&
    Target::codegen_get() const
    {
      return codegen_;
    }

    Codegen&
    Target::codegen_get()
    {
      return codegen_;
    }

  } // namespace mips
} // namespace target
