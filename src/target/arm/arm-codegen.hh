/**
 ** \file target/arm/arm-codegen.hh
 ** \brief Declaration of target::arm::Codegen.
 **/

#pragma once

#include <assem/libassem.hh>
#include <frame/access.hh>
#include <frame/frame.hh>
#include <target/arm/arm-assembly.hh>
#include <target/arm/cpu.hh>
#include <target/assembly.hh>
#include <target/codegen.hh>

namespace target::arm
{
  /// ArmCodegen.
  class ArmCodegen : public target::Codegen
  {
  public:
    typedef target::Codegen super_type;

    /// Construct an ARM code generator.
    ArmCodegen(bool rule_trace_p = false);

    /// Define the targeted ArmCpu.
    void cpu_set(const target::arm::Cpu& cpu);
    /// Access concrete CPU.
    const target::arm::Cpu* cpu_get() const;

    /// Set the ARM assembly language to use.
    void assembly_set(ArmAssembly& assembly);
    /// Access the current concrete assembly language.
    ArmAssembly& assembly_get();

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
        \see ArmCodegen::rewrite_program. */
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

    /// Entry point for code generation
    void codegen(const tree::rStm& root) override;

    /// The current Cpu with its real type: NolimipsCpu.
    const target::arm::Cpu* cpu_;

    /// Assembly language.
    ArmAssembly* assembly_;
  }; // class ArmCodegen

} // namespace target::arm
