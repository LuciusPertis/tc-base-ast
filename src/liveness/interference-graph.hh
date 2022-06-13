/**
 ** \file liveness/interference-graph.hh
 ** \brief Declare liveness::InterferenceGraph.
 */

#pragma once

#include <list>
#include <map>

#include <assem/libassem.hh>
#include <liveness/liveness.hh>
#include <misc/graph.hh>
#include <misc/set.hh>
#include <target/libtarget.hh>
#include <temp/fwd.hh>

namespace liveness
{
  /*--------------------.
  | InterferenceGraph.  |
  `--------------------*/

  /** \brief Provide liveness analysis.
   **
   ** The liveness of variables in control-flow is analyzed,
   ** producing an InterferenceGraph. */
  class InterferenceGraph : public misc::undirected_graph<temp::Temp>
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct an InterferenceGraph.
        \param name    its name, hopefully based on the function name
        \param instrs  the code snippet to study
        \param tempmap current Temp mapping
        \param trace   trace flag
    */
    InterferenceGraph(const std::string& name,
                      const assem::Instrs& instrs,
                      const temp::TempMap& tempmap,
                      bool trace = false);
    /** \} */

    /** \name Mapping from unique node decoration (the Temp) to
     ** the vertex_descriptor.
     ** \{ */
  private:
    /// Converting a temp::Temp into a unique integer.
    using temp2vertex = std::map<const temp::Temp, vertex_descriptor>;
    /// The mapping from temp::Temp to vertex_descriptor (= integer).
    temp2vertex temp2node_;
    /// The mapping from pseudos to actual registers.
    const temp::TempMap& tempmap_;

  public:
    /// Is the Temp \a t already part of the InterferenceGraph?
    bool has(const temp::Temp& t) const;
    /// From Temp to vertex_descriptor.  If \a t is not know yet, insert it.
    vertex_descriptor node_of(const temp::Temp& t);
    /** \} */

    /** \name Liveness analysis engine.
     ** \{ */
  protected:
    /* \brief Build the InterferenceGraph from \a liveness.

       \a Liveness remembers what is live at the exit of each
       flow-graph node.  Keep track of the moves.  Kept out of the
       ctor only to make it easier to read.  */
    void compute_liveness(const liveness::Liveness& liveness);
    /** \} */

    /** \name Moves.
        We keep track of all the moves so that we can try to coalesce
        destination and source.
        \{ */
  public:
    /** \brief A move is a pair (src, dst).

    Moves are not oriented, we chose to have pairs such that
    1st <= 2nd. */
    using move_type = std::pair<vertex_descriptor, vertex_descriptor>;

    /// Sets of moves.
    using move_set_type = misc::set<move_type>;

    /// Return the moves (const).
    const move_set_type& moves_get() const;
    /// Return the moves (non-const).
    move_set_type& moves_get();

    /// Get the liveness timer.
    const misc::timer& timer_get() const;

  protected:
    /// Include the move related edges in the output.
    std::ostream& epilogue_print(std::ostream& ostr) const override;
    /// Print the label of vertex of a graph.
    std::ostream& vertex_print(vertex_descriptor v,
                               std::ostream& ostr) const override;

    /// The set of moves.
    move_set_type moves_;
    /** \} */

    /** \name Trace methods.
     ** \{ */
    /// trace flag.
    bool trace_;
    /** \} */

    /** \name Timer member.
     ** \{ */
  private:
    /// Interference timer.
    misc::timer timer_;
    /** \} */

  }; // class InterferenceGraph

  /*------------.
  | Iterators.  |
  `------------*/

  /// Iterator on the vertices of an InterferenceGraph.
  using interferencegraph_vertex_iter_type =
    boost::graph_traits<InterferenceGraph>::vertex_iterator;

  /// Iterator on the neighborhood of a vertex of an InterferenceGraph.
  using interferencegraph_neighb_iter_type =
    boost::graph_traits<InterferenceGraph>::adjacency_iterator;

} // namespace liveness

#include <liveness/interference-graph.hxx>
