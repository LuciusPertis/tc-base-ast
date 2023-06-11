/**
 ** \file liveness/tasks.hh
 ** \brief Liveness module related tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace liveness::tasks
{
  TASK_GROUP("8. Liveness");

  /// Display the flowgraph
  TASK_DECLARE("F|flowgraph-dump",
               "dump the flowgraphs",
               flowgraph_dump,
               "inst-compute");

  /// Display the flowgraph with liveness information
  TASK_DECLARE("V|liveness-dump",
               "dump the liveness graphs",
               liveness_dump,
               "inst-compute");

  /// Display the interference graph
  TASK_DECLARE("N|interference-dump",
               "dump the interference graphs",
               interference_dump,
               "inst-compute");

} // namespace liveness::tasks
