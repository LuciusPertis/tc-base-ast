/**
 ** \file canon/basic-block.hh
 ** \brief Definition of canon::BasicBlock.
 */

#ifndef CANON_BASIC_BLOCK_HH
# define CANON_BASIC_BLOCK_HH

# include <iterator>
# include <algorithm>
# include <iosfwd>

# include <temp/fwd.hh>
# include <tree/fwd.hh>
# include <temp/label.hh>

namespace canon
{

  /** \brief A location independent piece of tree::Tree code.

  It starts with a tree::Label, ending with a tree::Jump or
  tree::CJump, and contains none of these three in between.
  Therefore, we may output it anywhere. */

  class BasicBlock
  {
  public:
    typedef tree::rTree      rTree;
    typedef tree::tree_list_type tree_list_type;

    /// Build a block with the instructions from \a begin to \a end.
    BasicBlock(tree_list_type::iterator begin, tree_list_type::iterator end);

    /// Append \a tree.
    const BasicBlock* push_back(const rTree& tree);

    /// The incoming label (that of the first instruction).
    temp::Label label_in_get() const;

    /// The list (one for Jump, two for CJump) of outgoing labels.
    temp::label_list_type labels_out_get() const;

    /// The list of instructions of this.
    tree_list_type& trees_get();

    /// Report this on \a ostr.
    std::ostream& dump(std::ostream& ostr) const;

  private:
    /// The Tree instructions.
    tree_list_type trees_;
  };

  /// Report \a block on \a ostr.
  std::ostream&
  operator<<(std::ostream& ostr, const BasicBlock& block);

}

# include <canon/basic-block.hxx>

#endif // !CANON_BASIC_BLOCK_HH
