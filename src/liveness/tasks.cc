/**
 ** \file liveness/tasks.cc
 ** \brief Liveness tasks implementation.
 */

#include <common.hh>
#include <liveness/libliveness.hh>
#define DEFINE_TASKS 1
#include <liveness/tasks.hh>
#undef DEFINE_TASKS
#include <misc/contract.hh>
#include <target/tasks.hh>
#include <temp/tasks.hh>

namespace liveness::tasks
{
  /** \brief Return the filename being computed.
   **
   ** Return the filename without the extension. For example
   ** "/a/b/c/d.tig" returns "d", used to produce dotty graph
   ** dumps (flowgraph, liveness and interference). */
  inline const std::string basename()
  {
    std::string fname = std::string(filename);
    return fname.substr(fname.rfind('/') + 1,
                        fname.length() - fname.rfind('/') - 5);
  }

  void flowgraph_dump()
  {
    precondition(target::tasks::fragments.get());
    liveness::flowgraph_dump(basename(), *target::tasks::fragments, task_timer);
  }

  void liveness_dump()
  {
    precondition(target::tasks::fragments.get());
    liveness::liveness_dump(basename(), *target::tasks::fragments,
                            *temp::tasks::tempmap, task_timer);
  }

  void interference_dump()
  {
    precondition(target::tasks::fragments.get());
    liveness::interference_dump(basename(), *target::tasks::fragments,
                                *temp::tasks::tempmap, task_timer);
  }

} // namespace liveness::tasks
