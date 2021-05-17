/**
 ** \file canon/canon.hh
 ** \brief Declaration canon::Canon.
 */

#pragma once

#include <tree/fwd.hh>

namespace canon
{
  /// Object function to canonicalize tree::Tree code.
  class Canon
  {
  public:
    /// Build a canonizer.
    Canon(bool trace_p = false);

    /// The actual worker.
    tree::rStm canon(tree::rStm stm);

    /*------------------.
    | Rewriting rules.  |
    `------------------*/

  private:
    /// Assemble statements \a s1 and \a s2 together.
    tree::rStm assemble_stm(const tree::rStm& s1, const tree::rStm& s2);

    /// Linearize \a seq: bubble up the sub SEQ, and get rid of nops.
    tree::rSeq linearize(const tree::rSeq& seq);

    /// Is \a call (LIR-)valid?
    bool valid_call(const tree::rCall& call);

    /** \brief Extract the side-effects of \a l.
      \return a pair of extracted side effets and a list of cleaned-up\
      statements. */
    std::pair<tree::rSeq, tree::tree_list_type>
    reorder(const tree::tree_list_type& l);

    /// Call pattern-matching on an \a exp to reorder it.
    tree::rEseq do_exp(const tree::rExp& exp);

    /// Call pattern-matching on an \a stm to reorder it.
    tree::rSeq do_stm(const tree::rStm& stm);

    /*-------------.
    | Attributes.  |
    `-------------*/
  private:
    /// Report debugging information.
    bool trace_p_;

    friend struct ExpMatcher;
    friend struct StmMatcher;
  };

} // namespace canon
