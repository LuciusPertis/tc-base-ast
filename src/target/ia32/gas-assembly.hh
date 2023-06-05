/**
 ** \file target/ia32/gas-assembly.hh
 ** \brief Declaration of target::ia32::GasAssembly.
 **/

#pragma once

#include <target/assembly.hh>

namespace target::ia32
{
  /** \brief Implements a GAS compatible assembly language.
   **
   ** See GAS, IA-32 emulator. */
  class GasAssembly : public Assembly
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a GasAssembly.
    GasAssembly();
    /** \} */

    /** \name Arithmetic instructions.
     ** \{ */
    std::string binop_inst(const tree::Binop::Oper& op) const;

    /// Build a binary (reg with reg in reg) operation in assembly.
    assem::Instrs binop_build(const tree::Binop::Oper& op,
                              const temp::Temp& left,
                              const temp::Temp& right,
                              const temp::Temp& res) const;

    /// Build a binary (imm with reg in reg) operation in assembly.
    assem::Instrs binop_build(const tree::Binop::Oper& op,
                              const temp::Temp& left,
                              int right,
                              const temp::Temp& res) const;
    /** \} */

    /** \name Copy instructions.
     ** \{ */
    /// Build a move (register into register) operation in assembly.
    assem::Instrs move_build(const temp::Temp& src,
                             const temp::Temp& dst) const;
    /** \brief Build a move (immediate into register) operation in
     ** assembly. */
    assem::Instrs move_build(int immediate, const temp::Temp& dst) const;

    /// Build a move (label into register) operation in assembly.
    assem::Instrs move_build(const temp::Label& label,
                             const temp::Temp& dst) const;

    /// Build a load (memory into register) operation in assembly.
    assem::Instrs
    load_build(const temp::Temp& base, int offset, const temp::Temp& dst) const;
    /// Build a load (memory into register) operation in assembly.
    assem::Instrs load_build(const temp::Temp& base,
                             const temp::Temp& dst) const;
    /// Build a load (memory into register) operation in assembly.
    assem::Instrs load_build(int absolute, const temp::Temp& dst) const;

    /// Build a store (register into memory) operation in assembly.
    assem::Instrs store_build(const temp::Temp& src,
                              const temp::Temp& base,
                              int offset = 0) const;
    /// Build a store (register into memory) operation in assembly.
    assem::Instrs store_build(const temp::Temp& src, int absolute) const;
    /** \} */

    /** \name Jump instructions.
     ** \{ */
    /// Build a label in assembly.
    assem::Instrs label_build(const temp::Label& label) const;

    /** \brief Return the assembly opcode of the conditional jump
        instruction corresponding to \a op. */
    std::string cjump_inst(const tree::Cjump::Relop& op) const;

    /// Build a reg/reg conditional jump.
    assem::Instrs cjump_build(const tree::Cjump::Relop& relop,
                              const temp::Temp& left,
                              const temp::Temp& right,
                              const temp::Label& label_true,
                              const temp::Label& label_false) const;

    /// Build a reg/imm conditional jump.
    assem::Instrs cjump_build(const tree::Cjump::Relop& relop,
                              const temp::Temp& left,
                              int right,
                              const temp::Label& label_true,
                              const temp::Label& label_false) const;

    /// Build an imm/reg conditional jump.
    assem::Instrs cjump_build(const tree::Cjump::Relop& relop,
                              int left,
                              const temp::Temp& right,
                              const temp::Label& label_true,
                              const temp::Label& label_false) const;

    /// Build an unconditional jump.
    assem::Instrs jump_build(const temp::Label& label) const;
    /** \} */

    /** \name Function operations.
     ** \{ */
    /// Build push instruction.
    assem::Instrs push_build(const temp::Temp& src);

    /// Build a function call in assembly.
    assem::Instrs call_build(const temp::Label& label,
                             const temp::temp_list_type& res) const;
    /// Revert caller's stack frame
    assem::Instrs leave_build() const;
    /// Build a function return in assembly.
    assem::Instrs ret_build(size_t i) const;
    /** \} */

    /** \name Runtime library.
     ** \{ */
    /// Return the runtime library.
    const char* runtime(bool gc = false) const override;
    /** \} */
  };
} // namespace target::ia32
