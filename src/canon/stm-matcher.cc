/**
 ** \file canon/stm-matcher.hh
 ** \brief Implementation of StmMatcher.
 */

#include <canon/stm-matcher.hh>

#include <misc/contract.hh>
#include <misc/list.hh>
#include <tree/all.hh>

namespace canon
{
  StmMatcher::StmMatcher(Canon* canon)
    : canon_(canon)
  {}

  tree::rSeq StmMatcher::operator()(tree::rSeq e)
  {
    if (!e->children_get().size())
      return e;

    auto begin = e->children_get().begin();
    auto end = e->children_get().end();

    auto child = begin->cast<tree::Stm>();
    tree::rStm stm = canon_->do_stm(child);

    for (auto it = begin + 1; it < end; it++)
      {
        child = it->cast<tree::Stm>();
        stm = canon_->assemble_stm(stm, canon_->do_stm(child));
      }

    return stm.cast<tree::Seq>();
  }

  tree::rSeq StmMatcher::operator()(tree::rJump e)
  {
    auto [stm, el] = canon_->reorder({e->exp_get()});

    auto [exp] = misc::list::decompose<1>(el);

    stm->emplace_back(new tree::Jump(exp.cast<tree::Exp>()));
    return stm;
  }

  tree::rSeq StmMatcher::operator()(tree::rCjump e)
  {
    auto [stm, el] = canon_->reorder({e->left_get(), e->right_get()});

    auto [left, right] = misc::list::decompose<2>(el);

    stm->emplace_back(new tree::Cjump(
      e->relop_get(), left.cast<tree::Exp>(), right.cast<tree::Exp>(),
      e->label_true_get(), e->label_false_get()));
    return stm;
  }

  tree::rSeq StmMatcher::operator()(tree::rMove e)
  {
    auto src = e->src_get();
    auto dst = e->dst_get();

    // A temp is not considered a subexpression since it is the destination of
    // the statement: its value is not used by the statement.
    if (dst.is_a<tree::Temp>())
      {
  // FIXME: Some code was deleted here.
      }

    // However, for a memory access the address acts like a source.
    if (dst.is_a<tree::Mem>())
      {
  // FIXME: Some code was deleted here.
      }

    // If the destination is an Eseq, we must prepose its statement and use its
    // expression as the destination of the move.
    if (dst.is_a<tree::Eseq>())
      {
  // FIXME: Some code was deleted here.
      }

    return default_match(e);
  }

  tree::rSeq StmMatcher::operator()(tree::rSxp e)
  {
    auto [stm, el] = canon_->reorder({e->exp_get()});

    auto [exp] = misc::list::decompose<1>(el);

    stm->emplace_back(new tree::Sxp(exp.cast<tree::Exp>()));
    return stm;
  }

  tree::rSeq StmMatcher::operator()(tree::rLabel e) { return default_match(e); }

  tree::rSeq StmMatcher::default_match(tree::rStm e)
  {
  // FIXME: Some code was deleted here.
  }

} // namespace canon
