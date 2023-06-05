/**
 ** \file target/mips/spim-matcher.hh
 ** \brief Declaration of target::mips::SpimMatcher.
 **/

#pragma once

#include <target/matcher.hh>

#include <target/mips/spim-codegen.hh>

namespace target::mips
{
  /// Pattern-matching visitor for mips codegen.
  struct SpimMatcher : public target::Matcher
  {
    using target::Matcher::operator();

    /** \brief Constructors.
     ** \{ */
    SpimMatcher() = delete;
    SpimMatcher(SpimCodegen* cg);
    /** \} */

    /** \name Exp pattern-matching operators.
     ** \{ */
    void operator()(tree::rBinop);
    void operator()(tree::rCall);
    void operator()(tree::rConst);
    void operator()(tree::rMem);
    void operator()(tree::rName);
    void operator()(tree::rTemp);
    /** \} */

    /** \name Stm pattern-matching operators.
     ** \{ */
    void operator()(tree::rCjump);
    void operator()(tree::rJump);
    void operator()(tree::rLabel);
    void operator()(tree::rMove);
    void operator()(tree::rSeq);
    void operator()(tree::rSxp);
    /** \} */

  private:
    /// The Codegen this matcher is part of.
    SpimCodegen* cg_;

    /** \name Auxiliary move matching functions.
     ** \{ */
    void move_load(tree::rExp exp, tree::rBinop binop);
    void move_store(tree::rExp exp, tree::rBinop binop);
    /** \} */
  };

} // namespace target::mips
