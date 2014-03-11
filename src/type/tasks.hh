/**
 ** \file type/tasks.hh
 ** \brief Type module tasks.
 */

#ifndef TYPE_TASKS_HH
# define TYPE_TASKS_HH

# include <task/libtask.hh>

namespace type
{

  namespace tasks
  {
    TASK_GROUP("4. Type checking");

    /// Default the type-checking to Tiger (without objects nor overloading).
    DISJUNCTIVE_TASK_DECLARE("T|typed",
                             "default the type-checking to Tiger "
                             "(without objects nor overloading)",
                             "types-compute"
                             " object-types-compute");

    /// Check for type violation.
    TASK_DECLARE("types-compute", "check for type violations",
                 types_check, "bindings-compute");
  } // namespace tasks

} // namespace type

#endif // !TYPE_TASKS_HH
