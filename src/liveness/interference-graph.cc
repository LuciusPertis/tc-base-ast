/**
 ** \file liveness/interference-graph.cc
 ** \brief Define the InterferenceGraph.
 */

#include <iostream>

#include <liveness/interference-graph.hh>
#include <misc/algorithm.hh>
#include <temp/temp.hh>

namespace liveness
{
  InterferenceGraph::InterferenceGraph(const std::string& name,
                                       const assem::Instrs& instrs,
                                       const temp::TempMap& tempmap,
                                       bool trace)
    : tempmap_(tempmap)
    , trace_(trace)
  {
    name_set(name);
    // First computation of FRAGMENT's liveness.
    // Compute it, name it, dump it if wanted.
    Liveness liveness(name, instrs, tempmap);
    if (trace_)
      liveness.print(name + ".liveness");

    timer_ << liveness.timer_get();

    // Analyze the liveness of variables in the control-flow graph.
    compute_liveness(liveness);
    if (trace_)
      print(name + ".interference");
  }

  bool InterferenceGraph::has(const temp::Temp& t) const
  {
    return temp2node_.find(t) != temp2node_.end();
  }

  InterferenceGraph::vertex_descriptor
  InterferenceGraph::node_of(const temp::Temp& t)
  {
    if (auto i = temp2node_.find(tempmap_(t)); i != temp2node_.end())
      return i->second;
    else
      return temp2node_[tempmap_(t)] = this->vertex_add(tempmap_(t));
  }

  void InterferenceGraph::compute_liveness(const Liveness& liveness)
  {
    if (trace_)
      std::cerr << "## Interference Graph: start.\n";
    timer_.push("8: interference graph");
  // FIXME: Some code was deleted here.
    timer_.pop("8: interference graph");
    if (trace_)
      std::cerr << "## Interference Graph: end.\n";
  }

  std::ostream& InterferenceGraph::epilogue_print(std::ostream& ostr) const
  {
    if (!moves_.empty())
      {
        ostr << "/* Move related edges. */\n";
        for (const move_type& m : moves_)
          ostr << "  \"" << m.first << "\" -- \"" << m.second << "\""
               << " [style=dashed]\n";
      }
    return ostr;
  }

  std::ostream& InterferenceGraph::vertex_print(vertex_descriptor v,
                                                std::ostream& ostr) const
  {
    return ostr << (*this)[v];
  }

} // namespace liveness
