/**
 ** \file canon/canon.cc
 ** \brief Canonicalizing HIR into LIR.
 */

#include <iostream>

#include <canon/canon.hh>
#include <canon/exp-matcher.hh>
#include <canon/stm-matcher.hh>
#include <misc/indent.hh>
#include <misc/list.hh>
#include <misc/vector.hh>
#include <temp/temp.hh>
#include <tree/all.hh>
#include <tree/tree-variants.hh>

namespace canon
{
  Canon::Canon(bool trace_p)
    : trace_p_(trace_p)
  {}

  /*----------------------.
  | Auxiliary functions.  |
  `----------------------*/

  namespace
  {
    /// \brief Return false if \a tree has to be run.
    /// Try to say true as much as possible.
    bool is_nop(const tree::rTree& tree)
    {
      // FIXME: Some code was deleted here.
    }

    /** \brief Return false if \a a and \a b cannot be swapped, try to
      say true as much as possible.

      Note that we are not trying to understand whether it is valid to
      swap \a a and \a b rather, we are checking if \a a can influence the
      meaning of \a b (or vice versa), in which case we must not permute
      them.  It is up to the caller to make proper use of this
      information.

      For instance in `BINOP(-, A, B)', if A and B are constants, the
      caller should not swap them, nevertheless this function shall
      return true.  */
    struct commute_p
    {
      commute_p(bool trace)
        : trace_(trace)
      {}

      bool commute_p_(const tree::rTree& a, const tree::rTree& b)
      {
        // FIXME: Some code was deleted here.
      }

      bool operator()(const tree::rTree& a, const tree::rTree& b)
      {
        // FIXME: Some code was deleted here.
      }

      bool trace_;
    };

  } // namespace

  /** Valid CALLs are:

  SXP(CALL ...)

  MOVE(TEMP, CALL ...) */
  bool Canon::valid_call(const tree::rCall& call)
  {
    precondition(call->parent_get());

    auto parent = call->parent_get();

    if (dynamic_cast<tree::Sxp*>(parent))
      return true;

    auto move = dynamic_cast<tree::Move*>(parent);
    if (!move)
      return false;

    if (!move->dst_get().is_a<tree::Temp>())
      return false;

    if (call != move->src_get())
      return false;

    return true;
  }

  // ----------------- //
  // Rewriting rules.  //
  // ----------------- //

  tree::rSeq Canon::assemble_seq(const tree::rSeq& s1, const tree::rSeq& s2)
  {
    if (!s1 || is_nop(s1))
      return s2;
    if (!s2 || is_nop(s2))
      return s1;

    tree::rSeq res = new tree::Seq;

    if (auto seq = s1.unsafe_cast<tree::Seq>())
      {
        append_and_move(res->children_get(), seq->children_get());
      }
    else
      res->emplace_back(s1);

    if (auto seq = s2.unsafe_cast<tree::Seq>())
      {
        append_and_move(res->children_get(), seq->children_get());
      }
    else
      res->emplace_back(s2);

    return res;
  }

  tree::rSeq Canon::assemble_seq(const tree::rSeq& s1, const tree::rStm& s2)
  {
    tree::rSeq res = new tree::Seq;

    append_and_move(res->children_get(), s1->children_get());
    res->emplace_back(s2);

    return res;
  }

  tree::rSeq Canon::linearize(const tree::rSeq& seq)
  {
    tree::tree_list_type res;
    tree::tree_list_type& children = seq->children_get();

    for (tree::rTree& t : children)
      {
        if (t.is_a<tree::Seq>())
          {
            tree::rSeq subseq = linearize(t.cast<tree::Seq>());
            append_and_move(res, subseq->children_get());
          }
        else if (!is_nop(t))
          res.emplace_back(t);
      }
    children = res;

    return seq;
  }

  std::pair<tree::rSeq, tree::tree_list_type>
  Canon::reorder(const tree::tree_list_type& l)
  {
    tree::tree_list_type res;

    if (l.empty())
      return {new tree::Seq(), res};

    auto [h, rest] = misc::list::snoc(l);

    // Here, Appel would handle invalid calls. We directly handle them in the
    // Visitor instead.

    precondition(h.is_a<tree::Exp>());
    auto [side_effects, exp] = do_exp(h.cast<tree::Exp>());

    auto [seq, el] = reorder(rest);

    commute_p commutes(trace_p_);
    if (commutes(seq, exp))
      {
        seq = assemble_seq(side_effects, seq).cast<tree::Seq>();

        res.emplace_back(exp);
      }
    else
      {
        temp::Temp t;

        auto tmp =
          assemble_seq(side_effects, new tree::Move(new tree::Temp(t), exp));
        seq = assemble_seq(tmp, seq).cast<tree::Seq>();

        res.emplace_back(new tree::Temp(t));
      }

    misc::append_and_move(res, el);
    return {seq, res};
  }

  std::pair<tree::rSeq, tree::rExp> Canon::do_exp(const tree::rExp& exp)
  {
    tree::ExpVariant var = exp->variant(exp);
    auto visitor = ExpMatcher(this);
    return var.visit(visitor);
  }

  tree::rSeq Canon::do_stm(const tree::rStm& stm)
  {
    tree::StmVariant var = stm->variant(stm);
    auto visitor = StmMatcher(this);
    return var.visit(visitor);
  }

  /*----------------------.
  | Main canon function.  |
  `----------------------*/

  tree::rStm Canon::canon(tree::rStm stm)
  {
    // 1. Canonicalize.
    if (trace_p_)
      std::cerr << "canon: in: " << &*stm << misc::incendl << *stm
                << misc::iendl;

    tree::rSeq res = do_stm(stm);

    if (trace_p_)
      std::cerr << "canon: out: " << &*res << misc::incendl << *res
                << misc::decindent << misc::decendl;

    // 2. Linearize
    if (trace_p_)
      std::cerr << "linearize: in:" << misc::incendl << *res << misc::decendl;

    res = linearize(res);

    if (trace_p_)
      std::cerr << "linearize: out:" << misc::incendl << *res << misc::decendl;

    return res;
  }

} // namespace canon
