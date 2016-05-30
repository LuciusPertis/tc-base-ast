/**
 ** \file target/arm/gas-layout.hh
 ** \brief Print assembly for ARM
 */

#pragma once

#include <assem/layout.hh>

namespace target
{
  namespace arm
  {

    /// Abstract ARM' fragments's layout.
    class ArmLayout : public assem::Layout
    {
      /** \name Construction.
       ** \{ */
    protected:
      /// Construct a ArmLayout.
      ArmLayout() = default;

    public:
      /// Return the unique instance of ArmLayout
      static ArmLayout& instance();
      /** \} */

      /** \name Fragments's visitor.
       ** \{ */
    public:
      /// Layout an assembly procedure fragment.
      void operator()(const assem::ProcFrag& a) override;
      /// Layout an assembly data fragment.
      void operator()(const assem::DataFrag& a) override;
    public:
      /// Layout a list of assembly fragments.
      void operator()(const assem::Fragments& a) override;
      /** \} */
    };

  } // namespace arm
} // namespace target
