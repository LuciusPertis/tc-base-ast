/**
 ** \file target/matcher.hh
 ** \brief Declaration of target::Matcher.
 **/

#pragma once

#include <target/codegen.hh>
#include <tree/all.hh>
#include <tree/fwd.hh>

namespace target
{
  ///Abstract pattern-matching visitor for codegen.
  struct Matcher
  {
    /** \name Pattern-matching entry points.
     ** \{ */
    void operator()(tree::rExp);
    void operator()(tree::rStm);
    /** \} */

    /// Eseqs should not be found in LIR.
    void operator()(tree::rEseq);

    /** \name Exp pattern-matching operators.
     ** \{ */
    virtual void operator()(tree::rBinop) = 0;
    virtual void operator()(tree::rCall) = 0;
    virtual void operator()(tree::rConst) = 0;
    virtual void operator()(tree::rMem) = 0;
    virtual void operator()(tree::rName) = 0;
    virtual void operator()(tree::rTemp) = 0;
    /** \} */

    /** \name Stm pattern-matching operators.
     ** \{ */
    virtual void operator()(tree::rCjump) = 0;
    virtual void operator()(tree::rJump) = 0;
    virtual void operator()(tree::rLabel) = 0;
    virtual void operator()(tree::rMove) = 0;
    virtual void operator()(tree::rSeq) = 0;
    virtual void operator()(tree::rSxp) = 0;
    /** \} */
  };

// Macros for convenient use of Codegen.
#define EMIT (cg_->emit)
#define ASSEMBLY (cg_->assembly_get())
#define FRAME (cg_->frame_get())
#define MCPU (*(cg_->cpu_get()))
#define REDUCE(What)                                                           \
  do                                                                           \
    {                                                                          \
      cg_->increase_indent();                                                  \
      if ((What)->reducible_get())                                             \
        tree::make_tree_variant(What).visit(*this);                            \
      cg_->decrease_indent();                                                  \
  } while (0)
#define TRACE (cg_->trace)

} // namespace target
