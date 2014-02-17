/**
 ** \file object/tasks.hh
 ** \brief Object module related tasks.
 */

#ifndef OBJECT_TASKS_HH
# define OBJECT_TASKS_HH

# include <task/libtask.hh>

namespace object
{

  /// The Tasks of the object module.
  namespace tasks
  {

    TASK_GROUP("Object");

    /// Enable object extensions.
    BOOLEAN_TASK_DECLARE("o|object", "enable object extensions",
                         enable_object_extensions_p, "");

    /// Parse the input file, allowing objects.
    TASK_DECLARE("object-parse", "parse a file, allowing objects",
                 object_parse, "object parse");




  } // namespace tasks

} // namespace object

#endif // !OBJECT_TASKS_HH
