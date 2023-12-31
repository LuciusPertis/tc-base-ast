/**
 ** \file misc/graph.hh
 ** \brief Undirected/oriented graph definition.
 */

#ifndef MISC_GRAPH_HH
# define MISC_GRAPH_HH

# include <iosfwd>
# include <list>
# include <set>
# include <string>
# include <vector>

/* Forward declarations to help the compiler not to mix up the
   namespace `target' with `boost::target'.  This happens in the
   instantiation of graph concepts in boost/graph/graph_concepts.hpp
   if this forward declaration is omitted.  */
#include <boost/graph/detail/edge.hpp>
namespace boost
{
  template <class OutEdgeListS, class VertexListS, class DirectedS,
           class VertexProperty, class EdgeProperty, class GraphProperty,
           class EdgeListS>
  class adjacency_list;

  template <class Directed, class Vertex, class OutEdgeListS,
           class VertexListS, class DirectedS, class VertexProperty,
           class EdgeProperty, class GraphProperty, class EdgeListS>
  inline Vertex
  target(const detail::edge_base<Directed, Vertex>& e,
         const adjacency_list<OutEdgeListS, VertexListS, DirectedS,
         VertexProperty, EdgeProperty, GraphProperty, EdgeListS>&);
} // namespace boost

# include <boost/graph/adjacency_list.hpp>

# include <misc/set.hh>

/// Handling of generic, oriented or undirected, graph.
namespace misc
{

  /*--------.
  | Graph.  |
  `--------*/

  /// Graph property: name.
  typedef boost::property<boost::graph_name_t, std::string> name_prop_type;

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  class graph
    : public boost::adjacency_list<boost::setS, boost::vecS, Orientation,
      VertexLabel, EdgeLabel,
      name_prop_type>
  {
  public:
    virtual ~graph();

  public:
    typedef graph<Orientation, VertexLabel, EdgeLabel> self_type;
    typedef boost::adjacency_list<boost::setS, boost::vecS, Orientation,
            VertexLabel, EdgeLabel,
            name_prop_type> super_type;
    typedef typename super_type::vertex_descriptor vertex_descriptor;

    /// Iterators.
  public:
    /// \{
    /// Iterator on the vertices of a graph.
    typedef typename boost::graph_traits<self_type>::vertex_iterator
    vertex_iter_type;
    /// Iterator on the edges of a graph.
    typedef typename boost::graph_traits<self_type>::edge_iterator
    edge_iter_type;
    /// \}

    /// Graph manipulation.
    /// \{
  public:
    /// \brief Add a vertex to the graph.
    ///
    /// Just a wrapper around boost::add_vertex.
    vertex_descriptor vertex_add(const VertexLabel& l);
    /// Add an edge between two vertices.
    virtual void
    edge_add(const vertex_descriptor& v1, const vertex_descriptor& v2) = 0;
    /// \}

    /// Graph pretty printing.
    /// \{
  public:
    virtual std::ostream& print(std::ostream& ostr) const;
    virtual std::ostream& epilogue_print(std::ostream& ostr) const;
    virtual void print(std::string file) const;

  private:
    /// Print the label of vertex of a graph.
    virtual std::ostream&
    vertex_print(vertex_descriptor v, std::ostream& ostr) const = 0;
    /// \}

    /// Graph name.
    /// \{
  public:
    const std::string& name_get() const;
    void name_set(const std::string& name);
    /// \}
  };

  template <typename Orientation, typename VertexLabel, typename EdgeLabel>
  std::ostream&
  operator<<(std::ostream& ostr,
             const graph<Orientation, VertexLabel, EdgeLabel>& g);

  // An helper class when we do not want any data attached to vertex
  // or an edge.
  struct empty {};
  inline std::ostream& operator<<(std::ostream& ostr, empty);


  /*----------------------------------------------------.
  | Specialization for directed (bidirectional) graph.  |
  `----------------------------------------------------*/

  /* Note that boost::bidirectionalS is like boost::directedS, except
     that it provides access to both in-edges and out-edges, whereas
     boost::directedS gives us only out-edges.  The consequence is
     that a bidirectional graph is twice as large as its directed
     version.  */
  template <typename VertexLabel = empty, typename EdgeLabel = empty>
  class directed_graph
    : public graph<boost::bidirectionalS, VertexLabel, EdgeLabel>
  {
  public:
    virtual ~directed_graph();

  public:
    typedef directed_graph<VertexLabel, EdgeLabel> self_type;
    typedef graph<boost::bidirectionalS, VertexLabel, EdgeLabel> super_type;
    typedef typename super_type::vertex_descriptor vertex_descriptor;

  public:
    /// Iterator on the vertices of a directed_graph.
    typedef typename boost::graph_traits<self_type>::vertex_iterator
    vertex_iter_type;
    /// Iterator on the neighbors of the vertex of a directed_graph.
    typedef typename boost::graph_traits<self_type>::adjacency_iterator
    neighb_iter_type;

    /// Iterators.
    /// \{
  public:
    /// \brief Add an edge between two vertices.
    ///
    /// This is just a wrapper around boost::add_edge.
    virtual void
    edge_add(const vertex_descriptor& v1,
             const vertex_descriptor& v2) override;
    /// \}

    /// \brief Topological sort.
    ///
    /// This version (algorithm 17.5 in Modern Compiler Implementation
    /// in ML, p. 390) is not the same as boost::topological_sort since
    /// the former works on directed acyclic graphs (DAGs) and the latter
    /// doesn't.
    ///
    /// \{
  public:
    std::list<vertex_descriptor> topological_sort() const;
  // FIXME: Some code was deleted here (You might want additional methods (this needs to be done in TC-8)).
    /// \}
  };


  /*--------------------------------------.
  | Specialization for undirected graph.  |
  `--------------------------------------*/

  template <typename VertexLabel = empty, typename EdgeLabel = empty>
  class undirected_graph
    : public graph<boost::undirectedS, VertexLabel, EdgeLabel>
  {
  public:
    virtual ~undirected_graph();

  public:
    typedef graph<boost::undirectedS, VertexLabel, EdgeLabel> super_type;
    typedef typename super_type::vertex_descriptor vertex_descriptor;

  public:
    /// \brief Add an edge between two vertices.
    ///
    /// Use this method instead of boost::add_edge directly to keep
    /// the order between the ends of an edge.
    virtual void
    edge_add(const vertex_descriptor& v1, const
             vertex_descriptor& v2) override;
  };

} // namespace misc

# include <misc/graph.hxx>

#endif // !MISC_GRAPH_HH
