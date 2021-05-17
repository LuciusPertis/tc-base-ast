/**
 ** \file canon/traces.hh
 ** \brief Composing traces from canon::BasicBlock's.
 */

#pragma once

#include <map>
#include <memory>
#include <canon/basic-block.hh>

namespace canon
{
  /// Object function to linearize canonicalized tree::Tree code.
  class Traces
  {
  public:
    Traces(bool trace_p = false);

    /// Linearize a canonicalized LIR fragment.
    tree::rStm operator()(const tree::rStm& tree);

  private:
    /*----------------------.
    | Making Basic Blocks.  |
    `----------------------*/

    /// Mapping a Label to the BasicBlock it starts.
    using block_map = std::map<temp::Label, std::unique_ptr<BasicBlock>>;

    /** \brief Split a low level tree into BasicBlocks.
        \param tree           the tree to split, a function's body
        \param entry_label    the entry label of this function's body
        \param epilogue_label the label to branch to at the end of the function.
    */
    block_map make_basic_blocks(const tree::rStm& tree,
                                const temp::Label& entry_label,
                                const temp::Label& epilogue_label);

    /// Sewing all the basic blocks into a single trace.
    /// Empties \a blocks.
    tree::tree_list_type make_trace(block_map& blocks,
                                    const temp::Label& entry_label,
                                    const temp::Label& epilogue_label);

    /*-------------------------.
    | Removing useless jumps.  |
    `-------------------------*/

    /** \brief Is the destination of the jump (pointed to by \a begin) one
        of the next labels?  */
    bool useless_jump_p(tree::tree_list_type::iterator begin,
                        tree::tree_list_type::iterator end);

    /** \brief Remove the useless jumps from \a trace.

    If the destination of a jump is one of the labels that follows,
    then it is useless.  Don't bother removing Labels: that
    requires checking they're not used elsewhere, and anyway Labels
    cost nothing.  */
    void strip_useless_jumps(tree::tree_list_type& trace);

  private:
    bool trace_p_;
  };
} // namespace canon
