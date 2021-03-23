/**
 ** \file src/translate/tasks.hh
 ** \brief Translate module tasks.
 */

#pragma once

#include <task/libtask.hh>
#include <tree/fwd.hh>

namespace translate::tasks
{
  /// The global translation of ast::tasks::the_program.
  extern std::unique_ptr<tree::Fragments> fragments;

  TASK_GROUP("5. Translation to High Level Intermediate Representation");

  /// Translate the AST to HIR.
  TASK_DECLARE("hir-compute", "translate to HIR", hir_compute, "typed");

  /// Translate the AST to HIR.
  TASK_DECLARE("H|hir-display", "display the HIR", hir_display, "hir-compute");



} // namespace translate::tasks
