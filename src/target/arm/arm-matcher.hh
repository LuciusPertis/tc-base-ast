/**
 ** \file target/arm/arm-matcher.hh
 ** \brief Declaration of target::arm::ArmMatcher.
 **/

#pragma once

#include <target/matcher.hh>

#include <target/arm/arm-codegen.hh>

namespace target::arm
{
  /// Pattern-matching visitor for arm codegen.
  struct ArmMatcher : public target::Matcher
  {
    using target::Matcher::operator();

    /** \brief Constructors.
     ** \{ */
    ArmMatcher() = delete;
    ArmMatcher(ArmCodegen* cg);
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
    ArmCodegen* cg_;

    /** \name Auxiliary move matching functions.
     ** \{ */
    void move_load(tree::rExp exp, tree::rBinop binop);
    void move_store(tree::rExp exp, tree::rBinop binop);
    /** \} */
  };

} // namespace target::arm
