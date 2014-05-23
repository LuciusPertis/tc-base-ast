/**
 ** \file canon/tasks.cc
 ** \brief Canon task implementations.
 */

#include <iostream>

#include <tree/fragments.hh>
#include <translate/tasks.hh>
#include <canon/libcanon.hh>
#define DEFINE_TASKS 1
#include <canon/tasks.hh>
#undef DEFINE_TASKS

namespace canon
{
  namespace tasks
  {

    /*------------------.
    | Canonical trees.  |
    `------------------*/

    void
    canon_compute()
    {
      canon::canonicalize(*translate::tasks::fragments, canon_trace_p);
    }

    void
    canon_display()
    {
      std::cout
        << "/* == Canonicalized Intermediate representation. == */"
        << std::endl
        << *translate::tasks::fragments;
    }



    /*---------.
    | Traces.  |
    `---------*/

    void
    traces_compute()
    {
      canon::make_traces(*translate::tasks::fragments, traces_trace_p);
    }


    /*----------------.
    | The whole job.  |
    `----------------*/

    void
    lir_compute()
    {
      /* Nothing to do: computing the LIR is the result of computing
         the traces, which is done by the task's dependencies.  */
    }

    void
    lir_display()
    {
      std::cout
        << "/* == Low Level Intermediate representation. == */"
        << std::endl
        << *translate::tasks::fragments;
    }
  } // namespace tasks

} // namespace canon
