/**
 ** \file assem/fwd.hh
 ** \brief Forward declarations for assem:: items.
 */

#pragma once

#include <iosfwd>

#include <misc/fwd.hh>

namespace assem
{
  // From layout.hh.
  class Layout;

  // From instr.hh.
  class Instr;

  // From instr.hh.
  class Instrs;

  // From fragment.hh.
  class Fragment;
  class ProcFrag;
  class DataFrag;
  std::ostream& operator<<(std::ostream& ostr, const Fragment& fragment);

  // From fragments.hh.
  class Fragments;

  // From visitor.hh.
  template <template <typename> class Const> class GenVisitor;
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace assem
