/**
 ** \file target/ia32/target.cc
 ** \brief Define the ia32::Target.
 */

#include <target/ia32/cpu.hh>
#include <target/ia32/gas-assembly.hh>
#include <target/ia32/gas-codegen.hh>
#include <target/ia32/target.hh>
#include <target/tasks.hh>

namespace target::ia32
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

  const GasCodegen& Target::codegen_get() const { return codegen_; }

  GasCodegen& Target::codegen_get() { return codegen_; }
} // namespace target::ia32
