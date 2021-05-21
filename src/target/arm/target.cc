/**
 ** \file target/arm/target.cc
 ** \brief Define the arm::Target.
 */

#include <target/arm/target.hh>
#include <target/tasks.hh>

namespace target::arm
{
  Target::Target(bool rule_trace_p)
    : codegen_(rule_trace_p)
  {
    codegen_.cpu_set(cpu_);
    codegen_.assembly_set(assembly_);
  }

  const Cpu& Target::cpu_get() const { return cpu_; }

  Cpu& Target::cpu_get() { return cpu_; }

  const Assembly& Target::assembly_get() const { return assembly_; }

  Assembly& Target::assembly_get() { return assembly_; }

  const ArmCodegen& Target::codegen_get() const { return codegen_; }

  ArmCodegen& Target::codegen_get() { return codegen_; }
} // namespace target::arm
