/**
 ** \file target/arm/arm-layout.hh
 ** \brief Print assembly for ARM
 */

#pragma once

#include <assem/layout.hh>

namespace target::arm
{
  /// Abstract ARM' fragments's layout.
  class ArmLayout : public assem::Layout
  {
    /** \name Construction.
     ** \{ */
  public:
    /// Return the unique instance of ArmLayout
    static ArmLayout& instance();
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
} // namespace target::arm
