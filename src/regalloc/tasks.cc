/**
 ** \file regalloc/tasks.cc
 ** \brief Regalloc task implementations.
 */

#include <common.hh>
#include <regalloc/libregalloc.hh>
#include <target/libtarget.hh>
#include <target/target.hh>
#include <target/tasks.hh>
#include <temp/tasks.hh>
#define DEFINE_TASKS 1
#include <regalloc/tasks.hh>
#undef DEFINE_TASKS

namespace regalloc::tasks
{
  void asm_compute()
  {
    using temp::tasks::tempmap;
    *tempmap = allocate_registers(*target::tasks::fragments,
                                  *target::tasks::target, *tempmap, task_timer,
                                  !asm_coalesce_disable_p, asm_trace_p);
    target::frame_allocate(*target::tasks::fragments, *target::tasks::target);
  }

  void asm_display() {}

} // namespace regalloc::tasks
