/**
 ** \file target/codegen.hh
 ** \brief Define the code generator mother class.
 */

#pragma once

#include <temp/fwd.hh>
#include <tree/fwd.hh>

#include <assem/fwd.hh>
#include <assem/instrs.hh>

#include <frame/fwd.hh>
#include <target/fwd.hh>

#include <misc/vector.hh>

namespace target
{
  /// Abstract a Code Generator.
  class Codegen
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct a Codegen.
    explicit Codegen(bool rule_trace_p = false);
    /// Destroy a Codegen.
    virtual ~Codegen() = default;
    /** \} */

    /** \name Code generation engine.
     ** \{ */
  protected:
    /// Launch code generation on the root statement.
    virtual void codegen(const tree::rStm& root) = 0;

  public:
    /// Generate code.
    assem::Instrs& codegen(const tree::rStm& stm, frame::Frame& frame);

    /** \brief Build part of the prologue and epilogue of the function.

    Free the callee save registers, and receive the arguments.
    Called as soon as the function body was translated.
    This is called "procEntryExit1" by Appel. */
    virtual void fragment_entry_exit_build(assem::ProcFrag& frag) = 0;

    /** \brief Allocate the frame.

    Called at the end, after register allocation, since the frame
    size depends upon it.  This is Appel's "procEntryExit3".  */
    virtual void frame_build(assem::ProcFrag& frag) const = 0;

    /** \brief Rewrite the code to spill the \a spilled.

    During register allocation, some temps could not be allocated
    a register and are \a spilled: rewrite the code to handle
    them (load and store where needed).  */
    virtual void rewrite_program(assem::ProcFrag& frag,
                                 const temp::temp_set_type& spilled,
                                 temp::temp_set_type& created_temps) const = 0;
    /** \} */

    /** \name Accessors.
     ** \{ */
  public:
    /// Access the abstract frame.
    frame::Frame& frame_get();

  protected:
    /// Access the list of built/being built instructions.
    assem::Instrs& instrs_get();
    /** \} */

  public:
    /// Append \a instr to the list of built instructions.
    void emit(assem::Instr* instr);
    /// Append \a instrs to the list of built instructions.
    void emit(assem::Instrs instrs);

    /// Emit a comment specifying the pattern-matching rule processed.
    virtual void trace(const std::string& rule);
    /// Increase rule trace indentation.
    virtual void increase_indent();
    /// Decrease rule trace indentation.
    virtual void decrease_indent();

  protected:
    /// Current frame may be resized for function's arguments.
    frame::Frame* frame_;

    /// Print rules when redicing.
    bool rule_trace_p_;
    /// Rule trace indentation.
    int indent_ = 0;

  private:
    /// The list of being built instructions.
    assem::Instrs instrs_;
  }; // class Codegen

} // namespace target

#include <target/codegen.hxx>
