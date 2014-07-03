/**
 ** \file regalloc/libregalloc.hh
 ** \brief Declares the Regalloc tasks.
 */

#ifndef REGALLOC_LIBREGALLOC_HH
# define REGALLOC_LIBREGALLOC_HH

# include <temp/fwd.hh>
# include <target/fwd.hh>
# include <misc/timer.hh>

/// Perform the register allocation.
namespace regalloc
{
  /// Color each member of \a fragments and return the register allocation.
  temp::TempMap
  allocate_registers(assem::Fragments& fragments,
                     const target::Target& target,
                     const temp::TempMap& tempmap,
                     misc::timer& t,
                     bool coalesce_enable_p = true,
                     bool regalloc_trace_p = false);

} // namespace regalloc

#endif // !REGALLOC_LIBREGALLOC_HH
