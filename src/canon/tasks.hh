/**
 ** \file canon/tasks.hh
 ** \brief Canon module tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace canon::tasks
{
  TASK_GROUP("6. Translation to Low Level Intermediate Representation");

  TASK_DECLARE("canon-compute", "canonicalize", canon_compute, "hir-compute");

  /// Shall we trace the canonicalization?
  BOOLEAN_TASK_DECLARE("canon-trace",
                       "trace the canonicalization of the LIR",
                       canon_trace_p,
                       "");

  TASK_DECLARE("C|canon-display",
               "display the canonicalized IR",
               canon_display,
               "canon-compute");

  TASK_DECLARE("traces-compute",
               "make traces",
               traces_compute,
               "canon-compute");

  /// Shall we trace the traces computation?
  BOOLEAN_TASK_DECLARE("traces-trace",
                       "trace the traces computation",
                       traces_trace_p,
                       "");

  TASK_DECLARE("lir-compute",
               "translate to LIR (alias for --trace-compute)",
               lir_compute,
               "traces-compute");

  TASK_DECLARE("L|lir-display",
               "display the low level intermediate representation",
               lir_display,
               "lir-compute");

} // namespace canon::tasks
