/**
 ** \file canon/traces.cc
 ** \brief Composing traces from canon::BasicBlock's.
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>

#include <canon/traces.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include <misc/vector.hh>
#include <range/v3/algorithm/find_if.hpp>
#include <range/v3/algorithm/remove.hpp>
#include <temp/fwd.hh>
#include <temp/identifier.hh>
#include <temp/label.hh>
#include <tree/all.hh>

namespace canon
{
  /*---------.
  | Traces.  |
  `---------*/

  Traces::Traces(bool trace_p)
    : trace_p_(trace_p)
  {}

  Traces::block_map Traces::make_basic_blocks(const tree::rStm& tree,
                                              const temp::Label& entry_label,
                                              const temp::Label& epilogue_label)
  {
    using namespace tree;

    /* Create the basic blocks from TREE, then store them in a map.  */
    block_map blocks;

  // FIXME: Some code was deleted here.

    return blocks;
  }

  tree::tree_list_type Traces::make_trace(block_map& blocks,
                                          const temp::Label& entry_label,
                                          const temp::Label& epilogue_label)
  {
    tree::tree_list_type res;

  // FIXME: Some code was deleted here.

    return res;
  }

  /*-------------------------.
  | Removing useless jumps.  |
  `-------------------------*/

  /// Is \a tree a JUMP(NAME())?  This is a predicate.
  struct jump_name_p
  {
  // FIXME: Some code was deleted here.
  };

  bool Traces::useless_jump_p(tree::tree_list_type::iterator begin,
                              tree::tree_list_type::iterator end)
  {
  // FIXME: Some code was deleted here.
  }

  void Traces::strip_useless_jumps(tree::tree_list_type& trace)
  {
  // FIXME: Some code was deleted here.
  }

  tree::rStm Traces::operator()(const tree::rStm& tree)
  {
    // 3. Basic Blocks.
    temp::Label entry_label;
    temp::Label epilogue_label;
    block_map basic_blocks =
      make_basic_blocks(tree, entry_label, epilogue_label);

    if (trace_p_)
      {
        std::cerr
          << "-------------------- Basic blocks ----------------------\n";
        for (block_map::value_type& b : basic_blocks)
          std::cerr << b.first << misc::incendl << *b.second << misc::decendl;
        std::cerr
          << "--------------------------------------------------------\n";
      }

    // 4. Making the trace.
    tree::tree_list_type trace =
      make_trace(basic_blocks, entry_label, epilogue_label);

    if (trace_p_)
      std::cerr
        << "------------------------- Trace -------------------------\n"
        << trace << '\n'
        << "---------------------------------------------------------\n";

    // 5. Remove useless JUMPS.
    strip_useless_jumps(trace);

    if (trace_p_)
      std::cerr
        << "--------- Trace with Useless Jumps Simplified -----------\n"
        << trace << '\n'
        << "---------------------------------------------------------\n";

    return new tree::Seq(trace);
  }

} // namespace canon
