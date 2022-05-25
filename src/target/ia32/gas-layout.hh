/**
 ** \file target/ia32/gas-layout.hh
 ** \brief Print assembly for IA-32 a la GAS
 */

#pragma once

#include <assem/layout.hh>

namespace target::ia32
{
  /// Abstract GAS' fragments's layout.
  class GasLayout : public assem::Layout
  {
    /** \name Construction.
     ** \{ */
  protected:
    /// Construct a GasLayout.
    GasLayout() = default;

  public:
    /// Return the unique instance of GasLayout
    static GasLayout& instance();
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
} // namespace target::ia32
