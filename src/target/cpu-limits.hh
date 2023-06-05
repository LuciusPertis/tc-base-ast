/**
 ** \file target/cpu-limits.hh
 ** \brief Declaration of target::CpuLimits
 */

#pragma once

#include <vector>

#include <temp/fwd.hh>

namespace target
{
  /// A set of restriction over a Cpu.
  class CpuLimits
  {
  public:
    /// Maximum number of callee save registers.
    int callee_save_max = 99;
    /// Maximum number of caller save registers.
    int caller_save_max = 99;
    /// Maximum number of argument passing registers.
    int argument_max = 99;
  };

} // namespace target
