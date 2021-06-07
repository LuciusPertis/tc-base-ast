/** \file regalloc/libregalloc.cc
 ** \brief Routines for register allocation. */

#include <assem/libassem.hh>
#include <regalloc/libregalloc.hh>
#include <regalloc/regallocator.hh>
#include <temp/temp.hh>

namespace regalloc
{
  /* Color each member of \a fragments and return the registers
     allocation.  */

  temp::TempMap allocate_registers(assem::Fragments& fragments,
                                   const target::Target& target,
                                   const temp::TempMap& tempmap,
                                   misc::timer& t,
                                   bool coalesce_enable_p,
                                   bool regalloc_trace_p)
  {
    RegisterAllocator allocator(target, tempmap, coalesce_enable_p,
                                regalloc_trace_p);
    allocator(fragments);

    t << allocator.timer_get();
    return allocator.allocation_get();
  }

} // namespace regalloc
