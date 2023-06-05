/**
 ** \file target/ia32/gas-matcher.hh
 ** \brief Declaration of target::ia32::GasMatcher.
 **/

#pragma once

#include <target/matcher.hh>

#include <target/ia32/gas-codegen.hh>

namespace target::ia32
{
  /// Pattern-matching visitor for ia32 codegen.
  struct GasMatcher : public target::Matcher
  {
    using target::Matcher::operator();

    /** \brief Constructors.
     ** \{ */
    GasMatcher() = delete;
    GasMatcher(GasCodegen* cg);
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
    GasCodegen* cg_;

    /** \name Auxiliary move matching functions.
     ** \{ */
    void move_load(tree::rExp exp, tree::rBinop binop);
    void move_store(tree::rExp exp, tree::rBinop binop);
    /** \} */
  };

} // namespace target::ia32
