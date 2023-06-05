/**
 ** \file assem/layout.hh
 ** \brief Abstract a fragments's layout.
 */

#pragma once

#include <iosfwd>

#include <assem/visitor.hh>
#include <temp/fwd.hh>

namespace assem
{
  /// Abstract a fragments's layout.
  class Layout : public ConstVisitor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    Layout();
    virtual ~Layout() = default;
    /** \} */

    /** \name Layout parameters.
     ** \{ */
  public:
    void ostr_set(std::ostream& ostr);
    void tempmap_set(const temp::TempMap& tempmap);
    void debug_set(bool debug);
    /** \} */

    /** \name Fragments's visitor.
     ** \{ */
  public:
    /// Layout an assembly procedure fragment.
    void operator()(const ProcFrag& a) override = 0;
    /// Layout an assembly data fragment.
    void operator()(const DataFrag& a) override = 0;
    /// Layout a list of assembly fragments.
    void operator()(const Fragments& frags) override;

  protected:
    std::ostream* postr_;
    /** \} */
  };

} // namespace assem

#include <assem/layout.hxx>
