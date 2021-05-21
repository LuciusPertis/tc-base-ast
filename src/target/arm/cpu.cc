/**
 ** \file target/arm/cpu.cc
 ** \brief Implementation for target/arm/cpu.hh.
 */

#include <misc/contract.hh>
#include <target/arm/cpu.hh>
#include <temp/temp.hh>

namespace target::arm
{
  Cpu::Cpu()
  {
    // General registers.

    argument_reg({"r1", "r2", "r3"});

    callee_save_reg({"r4", "r5", "r6", "r7", "r8", "r9", "r10"});

    special_reg({fp_reg(), sp_reg(), result_reg(), lr_reg()});

    (*tempmap_)["fp"] = fp_reg();
    (*tempmap_)["rv"] = result_reg();
  }

  size_t Cpu::word_size_get() const { return 4; }

  const temp::Temp& Cpu::fp_reg() const
  {
    static const temp::Temp fp("fp");
    return fp;
  }

  const temp::Temp& Cpu::sp_reg() const
  {
    static const temp::Temp sp("sp");
    return sp;
  }

  const temp::Temp& Cpu::lr_reg() const
  {
    static const temp::Temp lr("lr");
    return lr;
  }

  const temp::Temp& Cpu::result_reg() const
  {
    static const temp::Temp result("r0");
    return result;
  }
} // namespace target::arm
