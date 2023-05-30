/**
 ** \file canon/basic-block.cc
 ** \brief Implementation for canon::BasicBlock.
 */

#include <iostream>

#include <canon/basic-block.hh>
#include <misc/indent.hh>
#include <temp/label.hh>
#include <tree/all.hh>

namespace canon
{
  temp::label_list_type BasicBlock::labels_out_get() const
  {
    precondition(!trees_.empty());
    if (const auto last_jump = trees_.back().unsafe_cast<tree::Jump>())
      return last_jump->label_get();

    tree::rCjump last_cjump = trees_.back().cast<tree::Cjump>();
    return last_cjump->labels_get();
  }

  temp::Label BasicBlock::label_in_get() const
  {
    tree::rLabel label = trees_.front().cast<tree::Label>();
    assertion(label);
    return label->label_get();
  }

  std::ostream& BasicBlock::dump(std::ostream& ostr) const
  {
    return ostr << "BasicBlock (in = " << label_in_get()
                << ", out = " << labels_out_get() << ")" << misc::incendl
                << trees_ << misc::decindent;
  }

} // namespace canon
