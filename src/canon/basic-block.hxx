/**
 ** \file canon/basic-block.hxx
 ** \brief Inline methods for canon::BasicBlock.
 */

#pragma once

#include <canon/basic-block.hh>

namespace canon
{
  inline BasicBlock::BasicBlock(tree_list_type::iterator begin,
                                tree_list_type::iterator end)
    : trees_(tree_list_type(begin, end))
  {}

  inline const BasicBlock* BasicBlock::emplace_back(const rTree& tree)
  {
    trees_.emplace_back(tree);
    return this;
  }

  inline BasicBlock::tree_list_type& BasicBlock::trees_get() { return trees_; }

  inline std::ostream& operator<<(std::ostream& ostr, const BasicBlock& block)
  {
    return block.dump(ostr);
  }

} // namespace canon
