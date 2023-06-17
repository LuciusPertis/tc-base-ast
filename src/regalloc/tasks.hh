/**
 ** \file regalloc/tasks.hh
 ** \brief Declares the Regalloc tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace regalloc::tasks
{
  TASK_GROUP("9. Register Allocation");

  /// Disable coalescing.
  BOOLEAN_TASK_DECLARE("asm-coalesce-disable",
                       "disable coalescence",
                       asm_coalesce_disable_p,
                       "");

  /// Enable register allocation trace.
  BOOLEAN_TASK_DECLARE("asm-trace",
                       "trace register allocation",
                       asm_trace_p,
                       "");

  TASK_DECLARE("s|asm-compute",
               "allocate the registers",
               asm_compute,
               "inst-compute");

  TASK_DECLARE("S|asm-display",
               "display the final assembler",
               asm_display,
               "asm-compute runtime-display inst-display");

} // namespace regalloc::tasks
