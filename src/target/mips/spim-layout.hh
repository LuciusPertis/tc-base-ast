/**
 ** \file target/mips/spim-layout.hh
 ** \brief Declaration of target::mips::SpimLayout.
 */

#pragma once

#include <assem/layout.hh>

namespace target::mips
{
  /// Abstract SPIM's fragments's layout.
  class SpimLayout : public assem::Layout
  {
    /** \name Construction.
     ** \{ */
  protected:
    /// Construct a SpimLayout.
    SpimLayout() = default;

  public:
    /// Return the unique instance of SpimLayout.
    static SpimLayout& instance();
    /** \} */

    /** \name Fragments's visitor.
     ** \{ */
    /// Layout an assembly procedure fragment.
    void operator()(const assem::ProcFrag& a) override;
    /// Layout an assembly data fragment.
    void operator()(const assem::DataFrag& a) override;
    /// Layout a list of assembly fragments.
    void operator()(const assem::Fragments& a) override;
    /** \} */
  };
} // namespace target::mips
