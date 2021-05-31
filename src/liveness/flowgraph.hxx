/**
 ** \file liveness/flowgraph.hxx
 ** \brief Implementation for liveness/flowgraph.hh.
 */

#pragma once

#include <map>

#include <common.hh>
#include <liveness/flowgraph.hh>
#include <misc/contract.hh>

namespace liveness
{
  template <typename EdgeLabel>
  FlowGraph<EdgeLabel>::FlowGraph(const std::string& name,
                                  const assem::Instrs& instrs)
  {
    precondition(!instrs.empty());

    timer_.push("8: flow graph");
    this->name_set(name);

    // Create one node for each instruction and collect the labels in a map.
    // (The first node of the graph must be the first instruction).
  // FIXME: Some code was deleted here.

    // Create an edge between each branching instruction and
    // its destination labels.
  // FIXME: Some code was deleted here.
    timer_.pop("8: flow graph");
  }

  template <typename EdgeLabel>
  const misc::timer& FlowGraph<EdgeLabel>::timer_get() const
  {
    return timer_;
  }

  template <typename EdgeLabel>
  std::ostream& FlowGraph<EdgeLabel>::vertex_print(vertex_descriptor v,
                                                   std::ostream& ostr) const
  {
    return ostr << *(*this)[v];
  }

} // namespace liveness
