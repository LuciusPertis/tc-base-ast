/**
 ** \file callgraph/fundec-graph.hh
 ** \brief Declare and define fundec graph.
 */

#ifndef CALLGRAPH_FUNDEC_GRAPH_HH
# define CALLGRAPH_FUNDEC_GRAPH_HH

# include <map>
# include <boost/graph/adjacency_list.hpp>

# include <misc/graph.hh>

# include <ast/function-dec.hh>

namespace callgraph
{

  /*--------------.
  | FundecGraph.  |
  `--------------*/

  class FundecGraph
    : public misc::directed_graph<ast::FunctionDec*>
  {
  public:
    FundecGraph();
    virtual ~FundecGraph();

  public:
    /// Add a vertex to the graph, and attach a function definition to it.
    void fundec_add(ast::FunctionDec* f);
    /// Create an edge between to vertices, identified by the
    /// FunctionDec attached to each of them.
    void fundec_link(ast::FunctionDec* fu, ast::FunctionDec* fv);

  public:
    /// Retrieve the vertex handle corresponding to a FunctionDec.
    vertex_descriptor hfundec_get(ast::FunctionDec* f) const;

  protected:
    /// Print the label of vertex of a graph.
    virtual std::ostream&
    vertex_print(vertex_descriptor v, std::ostream& ostr) const override;

  protected:
    typedef std::map<ast::FunctionDec*, vertex_descriptor> hfundecs_type;
    hfundecs_type hfundecs;
  };

  typedef FundecGraph CallGraph;


  /*------------.
  | Iterators.  |
  `------------*/

  /// Iterator on the vertices of a FundecGraph.
  typedef boost::graph_traits<FundecGraph>::vertex_iterator
  fundecgraph_vertex_iter_type;
  /// Iterator on the edges of a FundecGraph.
  typedef boost::graph_traits<FundecGraph>::edge_iterator
  fundecgraph_edge_iter_type;
  /// Iterator on the neighborhood of a vertex of a FundecGraph.
  typedef boost::graph_traits<FundecGraph>::adjacency_iterator
  fundecgraph_neighb_iter_type;

  /// \name Aliases.
  /// \{
  /// Iterator on the vertices of a CallGraph.
  typedef fundecgraph_vertex_iter_type callgraph_vertex_iter_type;
  /// Iterator on the neighborhood of a vertex of a CallGraph.
  typedef fundecgraph_neighb_iter_type callgraph_neighb_iter_type;
  /// \}

} // namespace callgraph

# include <callgraph/fundec-graph.hxx>

#endif // !CALLGRAPH_FUNDEC_GRAPH_HH
