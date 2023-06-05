/**
 ** \file target/tasks.cc
 ** \brief Target tasks.
 */

#include <iostream>

#include <assem/fragments.hh>
#include <assem/instr.hh>
#include <frame/frame.hh>
#include <target/arm/target.hh>
#include <target/assembly.hh>
#include <target/cpu.hh>
#include <target/ia32/target.hh>
#include <target/libtarget.hh>
#include <target/mips/target.hh>
#include <target/target.hh>
#define DEFINE_TASKS 1
#include <target/tasks.hh>
#undef DEFINE_TASKS
#include <temp/tasks.hh>
#include <temp/temp.hh>
#include <translate/tasks.hh>

// Target task implementations.
namespace target::tasks
{
  CpuLimits limits;

  namespace
  {
    /// Change the globals depending upon the current target.
    Target* target_set(Target* t)
    {
      precondition(t);
      target.reset(t);
      temp::tasks::tempmap.reset(t->cpu_get().tempmap_get().clone());
      const Cpu& cpu = t->cpu_get();
      frame::word_size = cpu.word_size_get();
      return t;
    }

  } // namespace

  /** \brief Global target pointer.

      Pointer initialization is done in either target_mips or target_ia32,
      using target_set. One could want to set \a target in its construction,
      e.g., using target_set:

      \code
      std::unique_ptr<Target> target(target_set(...));
      \endcode

      but this would be dead wrong: target_set sets up several globals,
      such as temp::tasks::tempmap, that might not be instantiated yet!
      As a matter of fact, this is what happens on Mac OS X, where G++
      chose another order to perform its static initialization.
      Since the standard does say we should never depend on such an order,
      the easiest is to have a task perform the default assignment.

      In the long run, several of these globals should be removed.
      For instance, the temp::tasks::tempmap should probably be instantiated
      by the Target: therefore the dependencies issue will be magically
      resolved.
  */
  std::unique_ptr<Target> target(nullptr);

  /// Select MIPS target.
  void target_mips()
  {
    target_set(new ::target::mips::Target(limits, rule_trace_p));
  }

  /// Select IA-32 target
  void target_ia32() { target_set(new ::target::ia32::Target(rule_trace_p)); }

  /// Select ARM target
  void target_arm() { target_set(new ::target::arm::Target(rule_trace_p)); }

  /// Describe the current target.
  void target_display() { std::cout << *target; }

  /// Global assembly fragment list.
  std::unique_ptr<assem::Fragments> fragments;

  /// Perform the instruction selection.
  void inst_compute()
  {
    // Request target's assembly language program generation.
    fragments.reset(lir_to_assem(*translate::tasks::fragments, *target));
  }

  void runtime_display() { runtime_dump(*target, gc_p, std::cout); }

  /// Display the result of the instruction selection.
  void inst_display()
  {
    precondition(fragments.get());
    bool od = inst_debug_p;
    temp::TempMap* om = temp::tasks::tempmap.get();
    instructions_dump(*fragments, *target, *om, std::cout, od);
  }

  /// Display the result of instruction selection with frame allocation.
  void nolimips_display()
  {
    precondition(fragments.get());
    frame_allocate(*fragments, *target);
    // Ready to display instructions.
    inst_display();
  }

} // namespace target::tasks
