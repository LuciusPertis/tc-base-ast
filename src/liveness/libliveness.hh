/**
 ** \file liveness/libliveness.hh
 ** \brief Compute liveness analysis.
 */

#ifndef LIVENESS_LIBLIVENESS_HH
# define LIVENESS_LIBLIVENESS_HH

# include <iostream> // std::cout
# include <temp/fwd.hh>
# include <assem/fwd.hh>
# include <misc/timer.hh>

/// Generation of the FlowGraph, Liveness graph, and InterferenceGraph.
namespace liveness
{

  void
  flowgraph_dump(const std::string& filename,
                 const assem::Fragments& fragments,
                 misc::timer& timer);

  void
  liveness_dump(const std::string& filename,
                const assem::Fragments& fragments,
                const temp::TempMap& tempmap,
                misc::timer& timer);

  void
  interference_dump(const std::string& filename,
                    const assem::Fragments& fragments,
                    const temp::TempMap& tempmap,
                    misc::timer& timer);

} // namespace liveness

#endif // !LIVENESS_LIBLIVENESS_HH
