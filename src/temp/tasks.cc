/**
 ** \file temp/tasks.cc
 ** \brief Temp task implementations.
 */

#include <iostream>

#define DEFINE_TASKS 1
#include <temp/tasks.hh>
#undef DEFINE_TASKS
#include <temp/temp.hh>

namespace temp::tasks
{
  std::unique_ptr<TempMap> tempmap;

  /// Output \a tempmap on \a cout.
  void tempmap_display()
  {
    std::cout << "/* Temporary map. */\n" << *tempmap << '\n';
  }

} // namespace temp::tasks
