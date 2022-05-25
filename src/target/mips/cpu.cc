/**
 ** \file target/mips/cpu.cc
 ** \brief Define the MIPS Cpu.
 */

#include <memory>
#include <sstream>
#include <string>

#include <target/cpu-limits.hh>
#include <target/mips/cpu.hh>
#include <temp/temp.hh>

namespace target::mips
{
  /// Construct a Cpu (default).
  Cpu::Cpu(const CpuLimits& limits)
    : target::Cpu()
  {
    /// A TempMap that adjusts the output to Nolimips: t42 -> $x42.
    class NolimipsTempMap : public temp::TempMap
    {
    public:
      using super_type = temp::TempMap;

      NolimipsTempMap() = default;

      NolimipsTempMap* clone() const override
      {
        return new NolimipsTempMap(*this);
      }

      temp::Temp operator()(const temp::Temp& t) const override
      {
        temp::Temp res = t;
        if (auto ires = find(t); ires != end())
          res = ires->second;
        else if (t.prefix_get() == "t")
          {
            // This is admittedly a dirty hack to convert t13 into $x13.
            // We need inside knowledge.
            unsigned value = std::get<unsigned>(t.value_get());
            res = "$x" + std::to_string(value);
          }

        return res;
      }
    };

    // Replace the regular TempMap with a NolimipsTempMap.
    tempmap_ = std::make_unique<NolimipsTempMap>();

    // Caller save registers.
    switch (limits.caller_save_max)
      {
      default:
        caller_save_reg("$ra");
        [[fallthrough]];
      case 10:
        caller_save_reg("$t9");
        [[fallthrough]];
      case 9:
        caller_save_reg("$t8");
        [[fallthrough]];
      case 8:
        caller_save_reg("$t7");
        [[fallthrough]];
      case 7:
        caller_save_reg("$t6");
        [[fallthrough]];
      case 6:
        caller_save_reg("$t5");
        [[fallthrough]];
      case 5:
        caller_save_reg("$t4");
        [[fallthrough]];
      case 4:
        caller_save_reg("$t3");
        [[fallthrough]];
      case 3:
        caller_save_reg("$t2");
        [[fallthrough]];
      case 2:
        caller_save_reg("$t1");
        [[fallthrough]];
      case 1:
        caller_save_reg("$t0");
        [[fallthrough]];
      case 0:;
      }

    // Callee save registers.
    switch (limits.callee_save_max)
      {
      default:
        [[fallthrough]];
      case 8:
        callee_save_reg("$s7");
        [[fallthrough]];
      case 7:
        callee_save_reg("$s6");
        [[fallthrough]];
      case 6:
        callee_save_reg("$s5");
        [[fallthrough]];
      case 5:
        callee_save_reg("$s4");
        [[fallthrough]];
      case 4:
        callee_save_reg("$s3");
        [[fallthrough]];
      case 3:
        callee_save_reg("$s2");
        [[fallthrough]];
      case 2:
        callee_save_reg("$s1");
        [[fallthrough]];
      case 1:
        callee_save_reg("$s0");
        [[fallthrough]];
      case 0:;
      }

    // Argument registers.
    for (int i = 1; i <= std::min(4, limits.argument_max); ++i)
      switch (i)
        {
        case 4:
          argument_reg("$a3");
          break;
          [[fallthrough]];
        case 3:
          argument_reg("$a2");
          break;
          [[fallthrough]];
        case 2:
          argument_reg("$a1");
          break;
          [[fallthrough]];
        case 1:
          argument_reg("$a0");
          break;
        }

    // non-coalescable registers
    special_reg({zero_reg(), fp_reg(), result_reg(), sp_reg()});

    (*tempmap_)["fp"] = fp_reg();
    (*tempmap_)["rv"] = result_reg();
  }

  size_t Cpu::word_size_get() const { return 4; }

  const temp::Temp& Cpu::fp_reg() const
  {
    static const temp::Temp fp("$fp");
    return fp;
  }

  const temp::Temp& Cpu::sp_reg() const
  {
    static const temp::Temp sp("$sp");
    return sp;
  }

  const temp::Temp& Cpu::result_reg() const
  {
    static const temp::Temp result("$v0");
    return result;
  }

  const temp::Temp& Cpu::return_reg() const
  {
    static const temp::Temp return_adress("$ra");
    return return_adress;
  }

  const temp::Temp& Cpu::zero_reg() const
  {
    static const temp::Temp zero("$zero");
    return zero;
  }
} // namespace target::mips
