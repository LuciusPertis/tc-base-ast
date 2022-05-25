/**
 ** \file target/arm/arm-codegen.cc
 ** \brief Definition of target::gas::Codegen.
 **/

#include <target/ia32/gas-codegen.hh>

#include <target/ia32/gas-matcher.hh>
#include <tree/tree-variants.hh>

namespace target::ia32
{
  GasCodegen::GasCodegen(bool rule_trace_p)
    : target::Codegen(rule_trace_p)
    , cpu_(nullptr)
    , assembly_(nullptr)
  {}

  void GasCodegen::cpu_set(const target::ia32::Cpu& cpu) { cpu_ = &cpu; }

  const target::ia32::Cpu* GasCodegen::cpu_get() { return cpu_; }

  void GasCodegen::assembly_set(GasAssembly& assembly)
  {
    assembly_ = &assembly;
  }

  GasAssembly& GasCodegen::assembly_get()
  {
    assertion(assembly_);
    return *assembly_;
  }

  void GasCodegen::codegen(const tree::rStm& root)
  {
    assertion(cpu_);

    GasMatcher v(this);
    auto var = root->variant(root);
    var.visit(v);
  }

  assem::Instrs GasCodegen::store_inframe(const frame::Access* access,
                                          const temp::Temp& word,
                                          const temp::Temp& addr) const
  {
    auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
    return assembly_->store_build(word, addr, acc_frame.offset_get());
  }

  assem::Instrs GasCodegen::load_inframe(const frame::Access* access,
                                         const temp::Temp& word,
                                         const temp::Temp& addr) const
  {
    auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
    return assembly_->load_build(addr, acc_frame.offset_get(), word);
  }

  void GasCodegen::free_callee_save(assem::ProcFrag& frag)
  {
    // callee save registers interator.
    temp::temp_set_type callee = cpu_->callee_save_regs();

    assem::Instrs save, restore;
    for (const temp::Temp& t : callee)
      {
        // This is the temp where the callee save register is saved.
        temp::Temp temp;

        // Save the callee save register.
        misc::append_and_move(save, assembly_->move_build(t, temp));

        // Restore the callee save register.
        misc::append_and_move(restore, assembly_->move_build(temp, t));
      }

    // The instructions to modify.
    assem::Instrs& ins = frag.instrs_get();

    // Instruction iterator used to insert Moves which saves callee
    // save registers at the beginning of the fragment.
    misc::prepend_and_move(ins, save);
    misc::append_and_move(ins, restore);
  }

  void GasCodegen::view_shift(assem::ProcFrag& frag)
  {
    // Access to current Frame.
    frame::Frame& frame = frag.frame_get();

    // The instructions to modify.
    assem::Instrs& ins = frag.instrs_get();

    // Instruction iterator used to insert Moves which saves callee
    // save registers at the beginning of the fragment.
    auto instr_iter = ins.begin();

    // Formals: arguments as seen by the function.
    const frame::access_list_type& formals = frame.formals_get();
    auto formal_iter = formals.begin();

    // Move all the other arguments from the frame to
    // their dedicated location.
    for (size_t slot = cpu_->word_size_get() * 3; formal_iter != formals.end();
         ++formal_iter)
      {
        // A formal is either a InRegister (data is in a register) or
        // a InFrame (data is frame).
        auto acc_reg = dynamic_cast<const frame::InRegister*>(*formal_iter);

        if (acc_reg)
          // Formal type is InRegister.
          // Load the argument from the frame.
          instr_iter = std::next(misc::position_append_and_move(
            ins, instr_iter,
            assembly_->load_build(cpu_->fp_reg(), slot, acc_reg->temp_get())));
        else
          {
            // Formal type is InFrame.
            // Load the argument from the frame into a new temporary.
            temp::Temp temp;

            instr_iter = std::next(misc::position_append_and_move(
              ins, instr_iter,
              assembly_->load_build(cpu_->fp_reg(), slot, temp)));

            // Store the temporary to his dedicated location (in frame).
            instr_iter = std::next(misc::position_append_and_move(
              ins, instr_iter,
              store_inframe(*formal_iter, temp, cpu_->fp_reg())));
          }
        slot += cpu_->word_size_get();
      }
  }

  void GasCodegen::fragment_entry_exit_build(assem::ProcFrag& frag)
  {
    // Note that the order is reversed to what we want to obtain.

    // Save/restore callee save registers.
    free_callee_save(frag);

    // Implement the view shift.
    view_shift(frag);

    assem::Instrs& ins = frag.instrs_get();

    // The return adress is automatically stored-on/loaded-from
    // stack by `call' and `ret'.

    // Put frame allocation/deallocation markups
    auto frame_allocation_markup =
      new assem::Label("# Allocate frame", temp::Label("frame-allocation"));
    ins.emplace(ins.begin(), frame_allocation_markup);

    auto frame_deallocation_markup =
      new assem::Label("# Deallocate frame", temp::Label("frame-deallocation"));
    ins.emplace_back(frame_deallocation_markup);

    // Make fragment entry, prepending a definition of all the incoming
    // (conventionaly defined) registers.

    temp::Label entry_label("tc_" + frag.label_get().string_get());
    assem::Instrs frag_entry(assembly_->label_build(entry_label));

    frag_entry.front()->def() +=
      cpu_->argument_regs() + cpu_->callee_save_regs() + cpu_->special_regs();

    misc::prepend_and_move(ins, frag_entry);

    // Append the sink that specifies that some registers are really
    // special and are not to be used (e.g., $zero, $fp etc.).  We
    // also specify that callee save are live at the end, so that
    // the day we have dead code removal, they won't be thrown away
    // for lack of use.
    assem::Instrs frag_exit(assembly_->ret_build(
      frag.frame_get().formals_get().size() * cpu_->word_size_get()));
    frag_exit.back()->use() += cpu_->special_regs() + cpu_->callee_save_regs();

    misc::append_and_move(ins, frag_exit);
  }

  void GasCodegen::frame_build(assem::ProcFrag& frag) const
  {
    // Native IA-32 stack modifiers (push/pop, but also leave, ret
    // and call) follow a pre-decrementation post-incrementation
    // scheme, where %ebp and %esp always point to memory places
    // holding valid content. As TC internaly considers a
    // post-decremented pre-incrementated stack, the IA-32 back-end
    // must introduce instructions to synchronize these two
    // conventions. The most straightforward way to do it is to
    // modify base and stack pointers at the very beginning of the
    // routine.
    //
    // Thus, the famous prologue/epilogue section of an IA-32 routine:
    //
    //        pushl %ebp
    //        movl %esp, %ebp
    //
    //        # (%ebp) holds the value %esp had when entering
    //        # the routine, and must not be overwritten
    //
    //        movl %ebp, %esp
    //        popl %ebp
    //        ret $i
    //
    // Becomes:
    //
    //        pushl %ebp
    //        subl $4, %esp
    //        movl %esp, %ebp
    //
    //        # (%ebp) points to a "free" memory slot, as TC is expecting
    //
    //        movl %ebp, %esp
    //        addl $4, %esp
    //        popl %ebp
    //        ret $i
    //
    // As we prefer the "leave" instruction to restore the stack
    // ("leave" is faster than "movl %ebp, %esp; popl %ebp" since
    // the Pentium), we must generate the following, equivalent
    // epilogue:
    //
    //        addl $4, %ebp
    //        leave
    //        ret
    //
    // So don't be affraid to see "subl $4, %ESP" then "addl $4, %EBP"
    // it is exactly what we want.

    assem::Instrs& ins = frag.instrs_get();

    // 1. Prologue.

    auto frame_allocation_slot = ins.label_find("frame-allocation");
    assertion(frame_allocation_slot != ins.end());

    // Save the frame pointer in frame
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot, assembly_->push_build(cpu_->fp_reg())));

    // Counter the pre-dec/post-incrementation effect
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot,
      assembly_->binop_build(tree::Binop::Oper::sub, cpu_->sp_reg(),
                             cpu_->word_size_get(), cpu_->sp_reg())));

    // Move the stack pointer to the frame pointer (i.e. FP <= SP).
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot,
      assembly_->move_build(cpu_->sp_reg(), cpu_->fp_reg())));

    // Allocate the frame by decrementing the stack pointer.
    frame_allocation_slot = std::next(misc::position_append_and_move(
      ins, frame_allocation_slot,
      assembly_->binop_build(tree::Binop::Oper::sub, cpu_->sp_reg(),
                             frag.frame_get().get_current_frame_size(),
                             cpu_->sp_reg())));

    // Remove frame allocation markup
    delete *frame_allocation_slot;
    ins.erase(frame_allocation_slot);

    // 2. Epilogue.

    auto frame_deallocation_slot = ins.label_find("frame-deallocation");
    assertion(frame_deallocation_slot != ins.end());

    // Prepare frame restoration
    frame_deallocation_slot = std::next(misc::position_append_and_move(
      ins, frame_deallocation_slot,
      assembly_->binop_build(tree::Binop::Oper::add, cpu_->fp_reg(),
                             cpu_->word_size_get(), cpu_->fp_reg())));

    // Destroy the frame
    frame_deallocation_slot = std::next(misc::position_append_and_move(
      ins, frame_deallocation_slot, assembly_->leave_build()));

    // Remove frame deallocation markup
    delete *frame_deallocation_slot;
    ins.erase(frame_deallocation_slot);
  }

  void GasCodegen::rewrite_program(assem::ProcFrag& frag,
                                   const temp::temp_set_type& spilled,
                                   temp::temp_set_type& created_temps) const
  {
    // FIXME: Some code was deleted here (Needed in TC-9, when there are actual spills).
  }
} // namespace target::ia32
