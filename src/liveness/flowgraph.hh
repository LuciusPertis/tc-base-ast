/**
 ** \file liveness/flowgraph.hh
 ** \brief Representing and computing a flow graph.
 */

#pragma once

#include <assem/libassem.hh>
#include <misc/graph.hh>
#include <misc/timer.hh>

namespace liveness
{
  /// Flow graph.
  template <typename EdgeLabel = misc::empty>
  class FlowGraph : public misc::directed_graph<const assem::Instr*, EdgeLabel>
  {
  public:
    /// Shorthand for the current class type.
    using self_type = FlowGraph<EdgeLabel>;
    /// Shorthand for superclass.
    using super_type = misc::directed_graph<const assem::Instr*, EdgeLabel>;

    using vertex_descriptor = typename super_type::vertex_descriptor;

    FlowGraph(const std::string& name, const assem::Instrs& instrs);
    // The flowgraph timer.
    const misc::timer& timer_get() const;

  protected:
    /// Print the label of vertex of a graph.
    virtual std::ostream& vertex_print(vertex_descriptor v,
                                       std::ostream& ostr) const;

    /** \name Timer member.
     ** \{ */
    /// Flowgraph timer.
    misc::timer timer_;
    /** \} */
  };

} // namespace liveness

#include <liveness/flowgraph.hxx>
