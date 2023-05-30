/**
 ** \file canon/exp-matcher.hh
 ** \brief Implementation of ExpMatcher.
 */

#include <canon/exp-matcher.hh>

#include <misc/contract.hh>
#include <misc/list.hh>
#include <tree/all.hh>

namespace canon
{
  ExpMatcher::ExpMatcher(Canon* canon)
    : canon_(canon)
  {}

  ExpMatcher::res_t ExpMatcher::operator()(tree::rBinop e)
  {
    auto [seq, el] = canon_->reorder({e->left_get(), e->right_get()});

    auto [left, right] = misc::list::decompose<2>(el);

    return {seq,
            new tree::Binop(e->oper_get(), left.cast<tree::Exp>(),
                            right.cast<tree::Exp>())};
  }

  ExpMatcher::res_t ExpMatcher::operator()(tree::rMem e)
  {
    auto [seq, el] = canon_->reorder({e->exp_get()});

    auto [exp] = misc::list::decompose<1>(el);

    return {seq, new tree::Mem(exp.cast<tree::Exp>())};
  }

  ExpMatcher::res_t ExpMatcher::operator()(tree::rEseq e)
  {
    // FIXME: Some code was deleted here.
  }

  ExpMatcher::res_t ExpMatcher::operator()(tree::rCall e)
  {
    tree::tree_list_type to_reorder =
      misc::list::cons(e->func_get().cast<tree::Tree>(), e->args_get());

    auto [seq, el] = canon_->reorder(to_reorder);

    auto [f, args] = misc::list::snoc(el);

    auto new_call = new tree::Call(f.cast<tree::Exp>(), args);

    if (canon_->valid_call(e))
      {
        // FIXME: Some code was deleted here.
      }
    else
      {
        // FIXME: Some code was deleted here (If call is not valid, we have to extract it).
      }
  }

  ExpMatcher::res_t ExpMatcher::operator()(tree::rConst e)
  {
    return default_match(e);
  }

  ExpMatcher::res_t ExpMatcher::operator()(tree::rName e)
  {
    return default_match(e);
  }

  ExpMatcher::res_t ExpMatcher::operator()(tree::rTemp e)
  {
    return default_match(e);
  }

  ExpMatcher::res_t ExpMatcher::default_match(tree::rExp e)
  {
    // FIXME: Some code was deleted here.
  }

} // namespace canon
