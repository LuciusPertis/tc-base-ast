/**
 ** \file target/arm/target.hh
 ** \brief Define the ARM Target.
 */

#pragma once

#include <target/arm/arm-assembly.hh>
#include <target/arm/arm-codegen.hh>
#include <target/arm/cpu.hh>
#include <target/target.hh>

namespace target::arm
{
  /// An ARM Target is the union of an ARM Cpu and an ARM ArmCodegen.
  class Target : public target::Target
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    Target(bool rule_trace_p = false);
    /** \} */

    /// Access the ARM CPU (read only).
    const Cpu& cpu_get() const override;
    /// Access the ARM CPU.
    Cpu& cpu_get() override;

    /// Access the current assembly language (read only).
    const Assembly& assembly_get() const override;
    /// Access the current assembly language.
    Assembly& assembly_get() override;

    /// Access the current code generator (read only).
    const ArmCodegen& codegen_get() const override;
    /// Access the current code generator.
    ArmCodegen& codegen_get() override;

  protected:
    /// The description of an ARM CPU.
    arm::Cpu cpu_;
    /// The selected code generator
    arm::ArmCodegen codegen_;

    // This should be a arm::Assembly, dynamicaly set to
    // ArmAssembly or other.
    arm::ArmAssembly assembly_;
  };
} // namespace target::arm
