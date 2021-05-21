/**
 ** \file target/ia32/target.hh
 ** \brief Define the IA-32 Target.
 */

#pragma once

#include <target/ia32/cpu.hh>
#include <target/ia32/gas-assembly.hh>
#include <target/ia32/gas-codegen.hh>
#include <target/target.hh>

namespace target::ia32
{
  /// An IA-32 Target is the union of an IA-32 Cpu and an IA-32 Codegen.
  class Target : public target::Target
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    Target(bool rule_trace_p = false);
    /** \} */

    /// Access the IA-32 CPU (read only).
    const Cpu& cpu_get() const override;
    /// Access the IA-32 CPU.
    Cpu& cpu_get() override;

    /// Access the current assembly language (read only).
    const Assembly& assembly_get() const override;
    /// Access the current assembly language.
    Assembly& assembly_get() override;

    /// Access the current code generator (read only).
    const GasCodegen& codegen_get() const override;
    /// Access the current code generator.
    GasCodegen& codegen_get() override;

  protected:
    /// The description of an IA-32 CPU.
    ia32::Cpu cpu_;
    /// The selected code generator
    ia32::GasCodegen codegen_;

    // This should be a ia32::Assembly, dynamicaly set to
    // GasAssembly or other.
    ia32::GasAssembly assembly_;
  };
} // namespace target::ia32
