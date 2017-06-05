/**
 ** \file liveness/liveness.cc
 ** \brief Implementation of liveness::Liveness.
 */

#include <set>
#include <vector>
#include <ostream>

/* Help Boost 1.50 find boost::disable_if, required by
   boost/graph/reverse_graph.hpp (fixed in Boost 1.51).  */
#include <boost/utility/enable_if.hpp>
#include <boost/graph/reverse_graph.hpp>

#include <temp/temp.hh>
#include <liveness/liveness.hh>

namespace liveness
{

  Liveness::Liveness(const std::string& name,
                     const assem::Instrs& instrs,
                     const temp::TempMap& tempmap)
    : FlowGraph<temp::temp_set_type>(name, instrs)
  {
  // FIXME: Some code was deleted here (Compute IN and OUT).

    // Label the edges with the list of live temps, to aid debugging.
    timer_.push("8: liveness edges");
    liveness_edge_iter_type e;
    liveness_edge_iter_type end;
    for (std::tie(e, end) = boost::edges(*this); e != end; ++e)
      (*this)[*e] = misc::set_intersection(out[boost::source(*e, *this)],
                                           in[boost::target(*e, *this)]);
    timer_.pop("8: liveness edges");
  }

  const Liveness::livemap_type&
  Liveness::liveout_get() const
  {
    return out;
  }

  const Liveness::livemap_type&
  Liveness::livein_get() const
  {
    return in;
  }


} // namespace regalloc
