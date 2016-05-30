/**
 ** \file target/assembly.hh
 ** \brief Abstract an assembly language.
 */

#pragma once

#include <temp/fwd.hh>
#include <temp/label.hh>
#include <tree/fwd.hh>
#include <tree/binop.hh> // Binop::Oper.
#include <tree/cjump.hh> // Cjump::Relop.

#include <assem/fwd.hh>
#include <assem/instrs.hh>

namespace target
{

  /** \brief An assembly language comes with its syntax, its runtime library,
   ** and its layout of fragments.
   **
   ** See Builder and Factory 's design patterns. */
  class Assembly
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    Assembly(assem::Layout& layout);

    /// Destroy an Assembly.
    virtual ~Assembly();
    /** \} */

  public:
    /// The runtime library.
    virtual const char* runtime(bool gc = false) const = 0;

    /// Return Assembly layout.
    assem::Layout& layout_get();

  protected:
    /// The associated assembly layout.
    assem::Layout& layout_;
  };

} // namespace target
