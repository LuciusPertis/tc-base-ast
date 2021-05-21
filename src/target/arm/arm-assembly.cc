/**
 ** \file target/arm/arm-assembly.cc
 ** \brief Implementation of target::arm::ArmAssembly.
 */

#include <string>

#include <assem/libassem.hh>
#include <misc/contract.hh>
#include <target/arm/arm-assembly.hh>
#include <target/arm/arm-layout.hh>
#include <temp/label.hh>

namespace target::arm
{
  ArmAssembly::ArmAssembly()
    : Assembly(ArmLayout::instance())
  {}

  /*------------------------.
  | Arithmetic operations.  |
  `------------------------*/

  std::string ArmAssembly::binop_inst(const tree::Binop::Oper& op) const
  {
    switch (op)
      {
      case tree::Binop::Oper::add:
        return "add\t";
      case tree::Binop::Oper::sub:
        return "sub\t";
      case tree::Binop::Oper::mul:
        return "mul\t";
        // Let tree::Binop::div fail, since it needs a dedicated
        // construction.
      default:
        die("Should not be there.");
      };
  }

  assem::Instrs ArmAssembly::binop_build(const tree::Binop::Oper& op,
                                         const temp::Temp& left,
                                         const temp::Temp& right,
                                         const temp::Temp& dst) const
  {
    assem::Instrs res;
    // arm use three-address instructions
    // { add $left with $right into $dst }
    if (op == tree::Binop::Oper::div)
      die("Should not be here");
    else
      {
        std::string opcode = binop_inst(op) + "'d, 's, 's";
        res.emplace_back(new assem::Oper(opcode, {left, right}, {dst}));
      }

    return res;
  }

  assem::Instrs ArmAssembly::binop_build(const tree::Binop::Oper& op,
                                         const temp::Temp& left,
                                         int right,
                                         const temp::Temp& dst) const
  {
    if (op == tree::Binop::Oper::div)
      die("Should not be here");
    else if (op == tree::Binop::Oper::mul
             || (256 <= right && (1020 < right || right % 4 != 0)
                 && (right < 1024 || 4080 < right || right % 16 != 0)
                 && (right < 4096 || 16320 < right || right % 64 != 0)))
      {
        // An immediate constant for such operation
        // is represented by 12 bits:
        // - 8 bits for a number in range [0 - 255]
        // - 4 bits for an even number which is usedto
        // apply a ROR on the 8 previous bits
        //
        // With that configuration, some numbers cannot be
        // represented directly and need to be loaded via ldr
        // or movt/movw
        temp::Temp tp;
        assem::Instrs res;

        misc::append_and_move(res, move_build(right, tp));
        misc::append_and_move(res, binop_build(op, left, tp, dst));
        return res;
      }
    else
      {
        std::string opcode =
          binop_inst(op) + "'d, 's, #" + std::to_string(right);
        return {new assem::Oper(opcode, {left}, {dst})};
      }
  }

  /*------------------.
  | Move operations.  |
  `------------------*/

  assem::Instrs ArmAssembly::move_build(const temp::Temp& src,
                                        const temp::Temp& dst) const
  {
    return {new assem::Move("mov\t'd, 's", src, dst)};
  }

  assem::Instrs ArmAssembly::move_build(int immediate,
                                        const temp::Temp& dst) const
  {
    std::string opcode = "ldr\t'd, =" + std::to_string(immediate);
    return {new assem::Oper(opcode, {}, {dst})};
  }

  assem::Instrs ArmAssembly::move_build(const temp::Label& label,
                                        const temp::Temp& dst) const
  {
    return {new assem::Oper("ldr\t'd, =" + label.string_get(), {}, {dst})};
  }

  /*------------------.
  | Load operations.  |
  `------------------*/

  assem::Instrs ArmAssembly::load_build(const temp::Temp& base,
                                        int offset,
                                        const temp::Temp& dst) const
  {
    std::string opcode = "ldr\t'd, ['s, #" + std::to_string(offset) + "]";
    return {new assem::Oper(opcode, {base}, {dst})};
  }

  assem::Instrs ArmAssembly::load_build(const temp::Temp& base,
                                        const temp::Temp& dst) const
  {
    return load_build(base, 0, dst);
  }

  assem::Instrs ArmAssembly::load_build(int, const temp::Temp&) const
  {
    die("FIXME: invalid load instruction, (inverse arguments)");
  }

  /*-------------------.
  | Store operations.  |
  `-------------------*/

  assem::Instrs ArmAssembly::store_build(const temp::Temp& src,
                                         const temp::Temp& base,
                                         int offset) const
  {
    std::string opcode = "str\t's, ['s, #" + std::to_string(offset) + "]";
    return {new assem::Oper(opcode, {src, base}, {})};
  }

  assem::Instrs ArmAssembly::store_build(const temp::Temp&, int) const
  {
    die("FIXME: invalid store instruction, (inverse arguments)");
  }

  /*--------.
  | Label.  |
  `--------*/

  assem::Instrs ArmAssembly::label_build(const temp::Label& label) const
  {
    return {new assem::Label(label.string_get() + ":", label)};
  }

  /*-------------------.
  | Conditional jump.  |
  `-------------------*/

  std::string ArmAssembly::cjump_inst(const tree::Cjump::Relop& op) const
  {
    switch (op)
      {
      case tree::Cjump::Relop::eq:
        return "beq\t'j";
      case tree::Cjump::Relop::ne:
        return "bne\t'j";
      case tree::Cjump::Relop::lt:
        return "blt\t'j";
      case tree::Cjump::Relop::gt:
        return "bgt\t'j";
      case tree::Cjump::Relop::le:
        return "ble\t'j";
      case tree::Cjump::Relop::ge:
        return "bge\t'j";
      case tree::Cjump::Relop::ult:
        return "blo\t'j";
      case tree::Cjump::Relop::ugt:
        return "bhi\t'j";
      case tree::Cjump::Relop::ule:
        return "bls\t'j";
      case tree::Cjump::Relop::uge:
        return "bhs\t'j";
      default:
        die("Should not be there.");
      };
  }

  // if (left cc right) then jump to label_true
  //
  // cmp left, right
  // jcc  label_true

  assem::Instrs ArmAssembly::cjump_build(const tree::Cjump::Relop& op,
                                         const temp::Temp& left,
                                         const temp::Temp& right,
                                         const temp::Label& label_true,
                                         const temp::Label& label_false) const
  {
  // FIXME: Some code was deleted here.
  }

  assem::Instrs ArmAssembly::cjump_build(const tree::Cjump::Relop& op,
                                         const temp::Temp& left,
                                         int right,
                                         const temp::Label& label_true,
                                         const temp::Label& label_false) const
  {
  // FIXME: Some code was deleted here.
  }

  assem::Instrs ArmAssembly::cjump_build(const tree::Cjump::Relop& op,
                                         int left,
                                         const temp::Temp& right,
                                         const temp::Label& label_true,
                                         const temp::Label& label_false) const
  {
    return cjump_build(tree::symmetrize(op), right, left, label_true,
                       label_false);
  }

  /*---------------------.
  | Unconditional jump.  |
  `---------------------*/

  assem::Instrs ArmAssembly::jump_build(const temp::Label& label) const
  {
    return {new assem::Oper("b\t'j ", {}, {}, {label})};
  }

  /*-----------.
  | Function.  |
  `-----------*/

  assem::Instrs ArmAssembly::push_build(const temp::Temp& t1,
                                        const temp::Temp& t2) const
  {
    return {new assem::Oper("push\t{'s, 's}", {t1, t2}, {})};
  }

  assem::Instrs ArmAssembly::call_build(const temp::Label& label,
                                        const temp::temp_list_type& args,
                                        const temp::temp_list_type& dst) const
  {
    return {new assem::Oper("bl\ttc_" + label.string_get(), args, dst)};
  }

  assem::Instrs ArmAssembly::ret_build() const
  {
    return {new assem::Oper("pop\t{fp, pc}", {}, {})};
  }
} // namespace target::arm
