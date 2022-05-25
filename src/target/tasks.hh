/**
 ** \file target/tasks.hh
 ** \brief Target tasks.
 */

#pragma once

#include <assem/fragment.hh>
#include <target/cpu-limits.hh>
#include <target/fwd.hh>
#include <task/libtask.hh>

namespace target::tasks
{
  /// Global assembly fragment list.
  extern std::unique_ptr<assem::Fragments> fragments;

  /// Global target pointer (default is MIPS).
  extern std::unique_ptr<Target> target;

  /// A set of restrictions over the cpu.
  extern CpuLimits limits;

  TASK_GROUP("7. Target selection");

  /// Perform the instruction selection.
  TASK_DECLARE("i|inst-compute",
               "select the instructions",
               inst_compute,
               "lir-compute targeted");

  /// Display the runtime
  TASK_DECLARE("R|runtime-display",
               "display the runtime",
               runtime_display,
               "targeted");

  /// Report def, use and jump lists.
  BOOLEAN_TASK_DECLARE("inst-debug",
                       "enable instructions verbose display",
                       inst_debug_p,
                       "");

  /// Report rule reducing.
  BOOLEAN_TASK_DECLARE("rule-trace",
                       "enable rule reducing display",
                       rule_trace_p,
                       "");

  /// Enable support for the Boehm-Demers-Weiser garbage collector.
  BOOLEAN_TASK_DECLARE("garbage-collection",
                       "enable garbage collection",
                       gc_p,
                       "");

  /// Display the result of the instruction selection.
  TASK_DECLARE("I|inst-display",
               "display the instructions",
               inst_display,
               "inst-compute");

  /// Display the result of the instruction selection.
  TASK_DECLARE("Y|nolimips-display",
               "display Nolimips compatible instructions (i.e., allocate "
               "the frames and then display the instructions",
               nolimips_display,
               "inst-compute");

  /// Make sure the target is defined.
  DISJUNCTIVE_TASK_DECLARE("targeted",
                           "default the target to MIPS",
                           "target-mips target-ia32 target-arm");

  /// Select MIPS target.
  TASK_DECLARE("target-mips", "select MIPS as target", target_mips, "");

  /// Select IA-32 target.
  TASK_DECLARE("target-ia32", "select IA-32 as target", target_ia32, "");

  /// Select ARM target.
  TASK_DECLARE("target-arm", "select ARM as target", target_arm, "");

  /// Describe the current target.
  TASK_DECLARE("target-display",
               "display the current target",
               target_display,
               "targeted");

  /// The maximum number of callee save registers.
  INT_TASK_DECLARE("callee-save",
                   0,
                   99,
                   "max number of callee save registers",
                   limits.callee_save_max,
                   "");

  /// The maximum number of callee save registers.
  INT_TASK_DECLARE("caller-save",
                   0,
                   99,
                   "max number of caller save registers",
                   limits.caller_save_max,
                   "");

  /// The maximum number of callee save registers.
  INT_TASK_DECLARE("argument",
                   0,
                   99,
                   "max number of argument registers",
                   limits.argument_max,
                   "");

} // namespace target::tasks
