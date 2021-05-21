/**
 ** \file target/libtarget.hh
 ** \brief Generation of pseudo assembly (assem::Fragments) from
 ** LIR (tree::Fragments).
 */

#pragma once

#include <iostream> // std::cout

#include <assem/fwd.hh>
#include <target/fwd.hh>
#include <temp/temp.hh>
#include <tree/fwd.hh>

namespace target
{
  /// Produce architecture-dependent assembly instructions.
  assem::Fragments* lir_to_assem(const tree::Fragments& fragments,
                                 Target& target);

  /** Dump the runtime.

      \param target target machine.
      \param gc     enable garbage collection (meaningful on IA-32 only yet).
      \param str    output stream on which to dump the runtime.  */
  void runtime_dump(const Target& target,
                    bool gc = false,
                    std::ostream& str = std::cout);

  /// Print the instructions.
  void instructions_dump(assem::Fragments& fragments,
                         Target& target,
                         std::ostream& ostr = std::cout);

  /// Print the instructions, and replaces temporary with actual
  /// registers using \a tempmap.
  void instructions_dump(assem::Fragments& fragments,
                         Target& target,
                         temp::TempMap& tempmap,
                         std::ostream& ostr = std::cout,
                         bool instruction_debug_p = false);

  /// Prepare Nolimips display.
  void frame_allocate(assem::Fragments& fragments, const Target& target);

} // namespace target
