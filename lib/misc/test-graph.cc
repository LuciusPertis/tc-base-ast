/**
 ** Testing undirected graphs.
 */

#include <cstdlib>
#include <iostream>

#include <misc/graph.hh>

using namespace misc;

class graph_type
  : public undirected_graph<int, std::string>
{
public:
  virtual std::ostream&
  vertex_print(vertex_descriptor v, std::ostream& ostr) const
  {
    return ostr << (*this)[v];
  }
};

unsigned
urand(unsigned max)
{
  return rand() % max;
}

bool
consistency(graph_type& g)
{
  unsigned nb_states = 1 + urand(10);
  unsigned nb_edges  = 1 + urand(20);
  std::vector<graph_type::vertex_descriptor> conv(nb_states);

  for (unsigned i = 0; i < nb_states; ++i)
    conv[i] = g.vertex_add(i);
  for (unsigned i = 0; i < nb_edges; ++i)
    {
      unsigned from = urand(nb_states);
      unsigned to   = urand(nb_states);
      char buf[256];
      std::sprintf(buf, "%d: %d->%d", i, from, to);
      graph_type::edge_descriptor e =
        (boost::add_edge(conv[from], conv[to], g)).first;
      g[e] = buf;
    }

  graph_type::vertex_descriptor n(0);
  typedef boost::graph_traits<graph_type>::adjacency_iterator neighb_iter_type;
  neighb_iter_type p;
  neighb_iter_type p_end;
  for (boost::tie(p, p_end) = boost::adjacent_vertices(n, g);
       p != p_end; ++p)
    std::cout << (int) *p << std::endl;

  g.name_set("test-graph");
  g.print(std::cout);

  unsigned to_remove = urand(nb_states);
  // Remove at least one vertex.
  if (to_remove <= 0)
    ++to_remove;
  misc::set<graph_type::vertex_descriptor> removed;
  for (unsigned i = 0; i < to_remove; ++i)
    {
      // Select a valid vertex.
      graph_type::vertex_descriptor s;
      do
        s = conv[urand(nb_states)];
      while (std::find(boost::vertices(g).first, boost::vertices(g).second, s)
             == boost::vertices(g).second);
      removed.insert(s);
      // Remove all edges to and from vertex S.
      boost::clear_vertex(s, g);
      // Remove S.
      boost::remove_vertex(s, g);
    }

  graph_type::vertex_iter_type i;
  graph_type::vertex_iter_type i_end;
  for (boost::tie(i, i_end) = boost::vertices(g);
       i != i_end; ++i)
    if (removed.has(*i))
      return false;

  g.print(std::cout);

  return true;
}

int
main()
{
  graph_type g;
  consistency(g);
}
