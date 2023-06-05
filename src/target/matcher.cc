/**
 ** \file target/matcher.hh
 ** \brief Implementation of target::Matcher.
 **/

#include <target/matcher.hh>

#include <misc/contract.hh>
#include <tree/tree-variants.hh>

namespace target
{
  void Matcher::operator()(tree::rExp tree)
  {
    auto var = tree->variant(tree);
    var.visit(*this);
  }

  void Matcher::operator()(tree::rStm tree)
  {
    auto var = tree->variant(tree);
    var.visit(*this);
  }

  void Matcher::operator()(tree::rEseq) { unreachable(); }

} // namespace target
