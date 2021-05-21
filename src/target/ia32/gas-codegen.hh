/**
 ** \file target/ia32/codegen.hh
 ** \brief Declaration of target::ia32::Codegen.
 **/

#pragma once

#include <assem/libassem.hh>
#include <frame/access.hh>
#include <frame/frame.hh>
#include <target/assembly.hh>
#include <target/codegen.hh>
#include <target/ia32/cpu.hh>
#include <target/ia32/gas-assembly.hh>

namespace target::ia32
{
  /// GasCodegen.
  class GasCodegen : public target::Codegen
  {
  public:
    using super_type = target::Codegen;

  public:
    /// Construct an IA-32 code generator.
    GasCodegen(bool rule_trace_p = false);

  public:
    /// Define the targeted Ia32Cpu.
    void cpu_set(const target::ia32::Cpu& cpu);
    /// Access concrete CPU.
    const target::ia32::Cpu* cpu_get();

    /// Set the IA-32 assembly language to use.
    void assembly_set(GasAssembly& assembly);
    /// Access the current concrete assembly language.
    GasAssembly& assembly_get();

  public:
    /** \brief To be able to use the callee save registers (which
        are virtually live throught out the function), we move
        them into fresh temporaries.  The register allocation is
        then free either to use the callee regs and spill these
        temps, or not to use the callee and therefore coalesce the
        the temps: a big nop.  */
    virtual void free_callee_save(assem::ProcFrag& frag);

    /** \brief Receive the incoming arguments, and move them where
        appropriate. */
    virtual void view_shift(assem::ProcFrag& frag);

    /** \brief Build part of the prologue and epilogue of the function:
        free the callee save registers, and receive the arguments.
        Called as soon as the function body was translated.
        This is called "procEntryExit1" by Appel. */
    void fragment_entry_exit_build(assem::ProcFrag& frag) override;

    /** \brief Preserve fp, sp and the return address register in
        hardware frame: push them during procedure prologue, pop them
        at epilogue.  Allocate the hardware frame by subtracting its
        size from the stack pointer for the procedure body.  This is
        Appel's "procEntryExit3".  */
    void frame_build(assem::ProcFrag& frag) const override;

    /** \brief Rewrite the code to spill the \a spilled.
        \see Codegen::rewrite_program. */
    void rewrite_program(assem::ProcFrag& frag2rw,
                         const temp::temp_set_type& spilled_trees,
                         temp::temp_set_type& created_temps) const override;

  protected:
    /** \brief Emit an instruction to save \a word at the adress
        \a addr + the offset stored in the access (which is, in fact,
        an InFrame).

        ACCESS is of course an InFrame, but prototyped as Access to
        factor the dynamic_casts in here.  */
    assem::Instrs store_inframe(const frame::Access* access,
                                const temp::Temp& word,
                                const temp::Temp& addr) const;
    /** \brief same as store_inframe() except that it emit an instruction
        to load a word.  */
    assem::Instrs load_inframe(const frame::Access* access,
                               const temp::Temp& word,
                               const temp::Temp& addr) const;

  protected:
    /// Entry point for code generation
    void codegen(const tree::rStm& root) override;

  protected:
    /// The current Cpu with its real type: NolimipsCpu.
    const target::ia32::Cpu* cpu_;

    /// Assembly language.
    GasAssembly* assembly_;
  }; // class GasCodegen

} // namespace target::ia32
