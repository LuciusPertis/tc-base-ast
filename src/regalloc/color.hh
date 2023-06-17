/**
 ** \file regalloc/color.hh
 ** \brief Color an InterferenceGraph
 **/

#pragma once

#include <map>
#include <vector>

#include <liveness/flowgraph.hh>
#include <liveness/interference-graph.hh>
// FIXME: should be libtarget.hh
#include <target/target.hh>
#include <temp/fwd.hh>

namespace regalloc
{
  /// Just color the graph itself.
  class Color
  {
    // Shortand typedefs
  public:
    using InterferenceGraph = liveness::InterferenceGraph;
    using hnodes_iterator = liveness::interferencegraph_vertex_iter_type;

    using node_type = InterferenceGraph::vertex_descriptor;
    using node_set_type = misc::set<node_type>;
    using node_list_type = std::vector<node_type>;

    using move_type = InterferenceGraph::move_type;
    using move_set_type = InterferenceGraph::move_set_type;

    /** \brief Mapping a node to the moves it is involved in.
        The name "list" is due to Appel, but it appears to be a set. */
    using move_list_map_type = std::vector<move_set_type>;

    /// Mapping a node to a color.
    using color_map_type = std::vector<temp::Temp>;

    /// Mapping a coalesced node onto its representant.
    using alias_map_type = std::vector<node_type>;

    /** \name Ctor & dtor.
     ** \{ */
    /** \brief Initialize the register allocation.

    This is basically the "Build" routine in Appel.  */
    Color(assem::ProcFrag& frag,
          const target::Cpu& cpu,
          const temp::TempMap& tempmap,
          const temp::temp_set_type& already_spilled,
          bool coalesce_p = false,
          bool trace_p = false);
    /** \} */

    /** \name Time.
     ** \{*/
    // The color timer.
    const misc::timer& timer_get() const;
    /** \} */

    /** \name Pre-treatments.
        Used by the constructor.
        \{ */
  protected:
    /// Import the nodes from the InterferenceGraph ig_.
    void import_nodes();

    /// Import the moves from the InterferenceGraph ig_.
    void import_moves();

    /** \brief Precolor the hard registers (cpu registers) used in the
        interference graph. */
    void precolor();

    /** \brief Compute the number of defs and uses of each temporaries.

    These values are needed when searching a node to spill, with the
    lowest priority.
    \see spill () */
    void priorities_compute();

    /** \brief Compute the initial degree of each node.
        Don't forget hard registers have an infinite degree. */
    void degrees_compute();
    /** \} */

    /** \brief Add an edge between \a u and \a v, making sure to
        update their degree ("AddEdge"). */
    void add_edge(const node_type u, const node_type v);

    /** \brief Put node \a n in the appropriate work list.
        \see make_work_list. */
    void make_work_list(const node_type n);

    /// Initialize the work lists ("MakeWorklist").
    void make_work_list();

    /** \brief Return the neighbors of \a n ("Adjacent").

    Compared to using directly neighbors_of, pay special attention to
    nodes that were simplified.
    */
    node_set_type adjacent(const node_type n) const;

    /** \brief Return whether \a a and \a b are adjacent.
        This is performing the job of "adjSet" in Appel's book.

    Compared to using directly edge_exists, pay special attention to
    nodes that were simplified.
    */
    bool adjacent(const node_type a, const node_type b) const;

    /// The (active) moves involing \a n ("NodeMoves").
    move_set_type node_moves(const node_type n) const;

    /// node \a n is involved in a move ("MoveRelated").
    bool move_related(const node_type n) const;

    /** \name Coalescing criteria.
        \{ */

    /** \brief Check if coalescing a and b is conservative according
        to Briggs' criterion ("Conservative").

        Briggs: less than k neighbors of significant degree.  */
    bool coalesce_briggs_p(const node_type a, const node_type b) const;

    /** \brief Check if coalescing \a a and \a b is safe according
        to the George's criterion ("OK").

        George: Nodes \a a and \a b can safely coalesce if, for every
        neighbor t of \a b, either t already interfers with \a a, or
        t is of insignificant degree. */
    bool coalesce_george_p(const node_type a, const node_type b) const;
    /** \} */

    /// Perform one round of coalescence ("Coalesce").
    void coalesce();

    /** \brief Node \a u is involved in a move which status
        just changed: check whether it became simplifiable
        ("AddWorkList"). */
    void add_work_list(const node_type u);

    /** \brief Return the active node with whom \a a has been
        coalesced ("GetAlias").  */
    node_type get_alias(const node_type a) const;

    /** \brief Merge the nodes \a u and \a v.  Keep \a u as representative
        of both nodes, and move \a v in the appropriate side list
        ("Combine").

        \attention Be sure to read the correction published by Appel
        on his site, since there are mistakes in the algorithm of
        this function. */
    void combine(const node_type u, const node_type v);

    /// Freeze the moves involving \a u ("FreezeMoves").
    void freeze_moves(const node_type u);

    /// Perform one round of freezing nodes ("Freeze").
    void freeze();

    /// Perform one round of spilling ("SelectSpill").
    void select_spill();

    /// Simplify one insignificant degree node.
    void simplify();

    /** \brief Decrement the degree of \a n ("DecrementDegree").

    Removing a node from the graph involves decrementing the degree
    of its \e current neighbors.  If the degree of a neighbor is already
    less than K - 1 then the neighbor must be move-related, and is not
    added to the \a simplify_work_list_.  When the degree of a neighbor
    transitions from K to K - 1, moves associated with \e its neighbors
    may be enabled.

    The algorithm as specified by Appel may have a small period during
    which the invariants are not preserved.  When one successfully
    coalesce two different nodes a and b, they are combined (see combine).
    As part of this merge, nodes adjacent to b become adjacent to a:
    there is a call to \a add_edge, which increases the degree.  But
    this degree ought to decrement immediatly afterwards.  Now, it is
    possible under some conditions that the "add_edge" had increased
    the degree of a node from K - 1 to K<em>without moving the node
    from work list</em>.  And then decrement_degree will see that the degree
    was K, and therefore that the status of the node is to be changed.
    The problem is that its status was not updated by "add_edge", so a
    strict invariant check will see that we try to remove a node from
    spill_work_list_, where it is not.

    That's not a problem: just don't be too strict on the invariant
    check here.  */
    void decrement_degree(node_type n);

    /** \brief Enable the moves related to node \a n ("EnableMoves").

    Removing a node from the graph involves decrementing the degree
    of its /current/ neighbors.  If the degree of a neighbor is already
    less than K - 1 then the neighbor must be move-related, and is not
    added to the \a simplify_work_list_.  When the degree of a neighbor
    transitions from K to K - 1, moves associated with /its/ neighbors
    may be enabled. */
    void enable_moves(node_type n);

    /// Enable the moves related to \a nodes ("EnableMoves").
    void enable_moves(const node_set_type& nodes);

    /** \brief Try to assign a color to a node using, in this order:
        caller-saves, callee-saves, arguments and specials. */
    void assign_color(node_type n);

    /** \brief Pop the entire stack, assigning colors (coloration phase).

    Get successively the last node of the stack and try to color it,
    rebuilding the original graph, step by step.

    Look for the precoloration of some nodes, the interferences between
    two nodes (these nodes must not occupy the same register),
    and the coalesced nodes that occupy the same register.
    ("AssignColors"). */
    void assign_colors();

  public:
    /** \brief Perform the coloration: try to assign registers
        to temporaries. Return true if colored with success
        (no spill). */
    bool operator()();

    /** \name Accessors.
     ** \{ */
    /// Return the list of temporaries that have not been colored.
    const temp::temp_set_type spilled_get() const;

    /** \brief Return the register allocation for this fragment,
        i.e., the combination of coalesced registers and the temps we
        just colored.  */
    temp::TempMap tempmap_get() const;
    /** \} */

    /** \name Debugging.
        \{ */
  protected:
    /// The action \a what is performed about node \a n.
    void trace(const std::string& what, const node_type& n) const;

    /// The action \a what is performed about move \a m.
    void trace(const std::string& what, const move_type& m) const;

    /** \brief Print node \a n under a human readable form:
        the corresponding Temp. */
    void dump(std::ostream& ostr, const node_type& n) const;

    /// Human readable output of the set of nodes \a s.
    void dump(std::ostream& ostr, const node_set_type& s) const;

    /// Human readable output of the list of nodes \a s.
    void dump(std::ostream& ostr, const node_list_type& s) const;

    /** \brief Print move \a m under a human readable form:
        with the corresponding Temp's. */
    void dump(std::ostream& ostr, const move_type& s) const;

    /// Human readable output of the set of moves \a s.
    void dump(std::ostream& ostr, const move_set_type& s) const;

    /// Human readable output of this Color object.
    void dump(std::ostream& ostr) const;
    /** \} */

  protected:
    /// The interference graph.
    InterferenceGraph ig_;

    /// Target architecture's cpu description.
    const target::Cpu& cpu_;

    /// The number of registers (number of colors).
    size_t nb_regs_;

    /// The instructions' fragments.
    assem::ProcFrag& asm_proc_frag_;

    /// trace flag.
    bool trace_p_;

    /// A flag to know if try to coalesce when we can
    bool coalesce_p_;

    /** \name Node work-lists, sets, and stacks.
        The following lists and sets are mutually disjoint and every
        node is always in exactly one of the sets or lists.
        The names used by Appel are provided in parentheses.

        \{ */

    /// Machine registers, preassigned a color ("precolored").
    node_set_type precolored_;

    /** \brief Temporary registers, not precolored and not yet
        processed ("initial").  */
    node_set_type initial_;

    /** \brief List of low-degree non-move-related nodes
        ("simplifyWorkList").  Actually a set.  */
    node_set_type simplify_work_list_;

    /** \brief List of low-degree move-related nodes ("freezeWorkList").
        Actually a set.   */
    node_set_type freeze_work_list_;

    /** \brief List of high-degree nodes ("spillWorkList").
        Actually a set. */
    node_set_type spill_work_list_;

    /** \brief Nodes marked for spilling during this round; initially
        empty ("spilledNodes").  */
    node_set_type spilled_nodes_;

    /** \brief Registers that have been coalesced; when u := v is
        coalesced, "v" is added to this set and "u" put back on some
        work-list (or vice versa) ("coalescedNodes").  */
    node_set_type coalesced_nodes_;

    /// Nodes successfully colored ("coloredNodes").
    node_set_type colored_nodes_;

    /** \brief Stack containing temporaries removed from the graph
        ("selectStack"). */
    node_list_type select_stack_;

    /** \} */

    /** \name Moves sets.
        There are five sets of move instructions, and every
        move is in exactly one of these sets (after "Build" through
        the end of "Main").
        \{ */

    /// Moves that have been coalesced ("coalescedMoves").
    move_set_type coalesced_moves_;

    /// Moves whose source and target interfere ("constrainedMoves").
    move_set_type constrained_moves_;

    /** \brief Moves that will no longer be considered for coalescing
        ("frozenMoves").  */
    move_set_type frozen_moves_;

    /// Moves enabled for possible coalescing ("workListMoves").
    move_set_type work_list_moves_;

    /// Moves not yet ready for coalescing ("activeMoves").
    move_set_type active_moves_;

    /** \} */

    /** \name Other data structures.
        \{ */

    /// The current degree of each node ("degree").
    std::vector<size_t> degree_;

    /** \brief A mapping from a node to the list of moves it is
        associated with ("moveList"). */
    move_list_map_type move_list_;

    /** \brief When a "move (u, v)" has been coalesced and "v" put
        in \a coalesced_nodes_, then "alias(v) = u" ("alias").  */
    alias_map_type alias_;

    /** \brief The color chosen by the algorithm for a node; for
        precolored nodes, this is initialized to the given color
        ("color").  */
    color_map_type color_;

    /** \brief Nodes already spilled in a previous run
        should have the lowest priority for a potential spill */
    const temp::temp_set_type& already_spilled_;

    /** \} */

    /// Number of uses/defs of each temporaries
    std::map<temp::Temp, int> temps_priority_;

    /** \name Timer member.
     ** \{ */
  private:
    /// Color timer.
    misc::timer timer_;
    /** \} */
  };

} // namespace regalloc
