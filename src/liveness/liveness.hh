/**
 ** \file liveness/liveness.hh
 ** \brief Declaration of liveness::Liveness.
 */

#pragma once

#include <map>

#include <boost/graph/reverse_graph.hpp>

#include <assem/libassem.hh>
#include <liveness/flowgraph.hh>
#include <temp/temp-set.hh>

namespace liveness
{
  /// FlowGraph labeled with live Temp.
  class Liveness : public FlowGraph<temp::temp_set_type>
  {
  public:
    /// Superclass.
    using super_type = FlowGraph<temp::temp_set_type>;

    using livemap_type = std::map<vertex_descriptor, temp::temp_set_type>;

    /** \brief Compute the liveness of variables in the flow-graph by
        iteration.

        This implementation is based on the algorithm 17.6 described in
        Modern Compiler Implementation in Java written by A. Appel. This
        is a work-list algorithm which keeps track of what must be
        recalculated.

        In the opposite of the algorithm 17.6, we switch in and out sets
        as well as predecessor and successor uses.
        For example, old <- out[n] => old <- in[n].

        Beware to not use the algorithm 10.4 as it takes a lot longer
        than the algorithm 17.6 which may lead some tests to not pass.

        \attention When displayed, the Liveness graph is a good means to
        check that the compiler works properly, including \em after the
        register allocation: we want to check that the liveness of the
        hard registers is properly understood.  But the Liveness graph is
        built thanks to the def and use of the instructions which are
        composed of temporaries (not hard registers).  So to be able to
        use the Liveness graph after register allocation, we must take
        the temp::tasks::tempmap into account below.

        \param name    name of this graph, hopefully based on the function name
        \param instrs  the assembly program of which compute the liveness graph
        \param tempmap a mapping to apply on \a instrs.
    */
    Liveness(const std::string& name,
             const assem::Instrs& instrs,
             const temp::TempMap& tempmap);

    const livemap_type& liveout_get() const;
    const livemap_type& livein_get() const;

  private:
    livemap_type in;
    livemap_type out;
  };

  /*------------.
  | Iterators.  |
  `------------*/

  /// Iterator on the vertices of a Liveness.
  using liveness_vertex_iter_type =
    boost::graph_traits<Liveness>::vertex_iterator;
  /// Iterator on the edge of a Liveness.
  using liveness_edge_iter_type = boost::graph_traits<Liveness>::edge_iterator;
  /// Iterator on the neighborhood of the vertices of a Liveness.
  using liveness_neighb_iter_type =
    boost::graph_traits<Liveness>::adjacency_iterator;
  /// Iterator on the neighborhood of the vertices of a reverse
  /// liveness graph.
  using reverse_liveness_neighb_iter_type =
    boost::graph_traits<boost::reverse_graph<Liveness>>::adjacency_iterator;

} // namespace liveness
