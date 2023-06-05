/**
 ** \file target/ia32/codegen.hh
 ** \brief Definition of target::mips::Codegen.
 **/

#include <target/mips/spim-codegen.hh>

#include <target/mips/spim-matcher.hh>
#include <tree/tree-variants.hh>

namespace target::mips
{
  SpimCodegen::SpimCodegen(bool rule_trace_p)
    : target::Codegen(rule_trace_p)
    , cpu_(nullptr)
    , assembly_(nullptr)
  {}

  void SpimCodegen::cpu_set(const target::mips::Cpu& cpu) { cpu_ = &cpu; }

  const target::mips::Cpu* SpimCodegen::cpu_get() { return cpu_; }

  void SpimCodegen::assembly_set(SpimAssembly& assembly)
  {
    assembly_ = &assembly;
  }

  SpimAssembly& SpimCodegen::assembly_get()
  {
    assertion(assembly_);
    return *assembly_;
  }

  void SpimCodegen::codegen(const tree::rStm& root)
  {
    assertion(cpu_);

    SpimMatcher v(this);
    auto var = root->variant(root);
    var.visit(v);
  }

  assem::Instrs SpimCodegen::store_inframe(const frame::Access* access,
                                           const temp::Temp& word,
                                           const temp::Temp& addr) const
  {
    auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
    return assembly_->store_build(word, addr, acc_frame.offset_get());
  }

  assem::Instrs SpimCodegen::load_inframe(const frame::Access* access,
                                          const temp::Temp& word,
                                          const temp::Temp& addr) const
  {
    auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
    return assembly_->load_build(addr, acc_frame.offset_get(), word);
  }

  void SpimCodegen::free_callee_save(assem::ProcFrag& frag)
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

  void SpimCodegen::view_shift(assem::ProcFrag& frag)
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

    // Arguments: registers where the arguments are received from.
    const temp::temp_list_type& args = cpu_->argument_regs();
    auto arg_iter = args.begin();

    // Move registers argument to their dedicated location.
    for (; formal_iter != formals.end() && arg_iter != args.end();
         ++formal_iter, ++arg_iter)
      {
        // A formal is either a InRegister (data is in a register) or
        // a InFrame (data is frame).
        auto acc_reg = dynamic_cast<const frame::InRegister*>(*formal_iter);

        if (acc_reg)
          // Formal type is InRegister.
          instr_iter = std::next(misc::position_append_and_move(
            ins, instr_iter,
            assembly_->move_build(*arg_iter, acc_reg->temp_get())));
        else
          // Formal type is InFrame.
          instr_iter = std::next(misc::position_append_and_move(
            ins, instr_iter,
            store_inframe(*formal_iter, *arg_iter, cpu_->fp_reg())));
      }

    // Move all the other arguments from the frame to
    // their dedicated location.
    for (size_t slot = cpu_->word_size_get(); formal_iter != formals.end();
         ++formal_iter)
      {
        // A formal is either a InRegister (data is in a register) or
        // a InFrame (data is frame).
        auto acc_reg = dynamic_cast<const frame::InRegister*>(*formal_iter);

        if (acc_reg)
          {
            // Formal type is InRegister.
            // Load the argument from the frame.
            instr_iter = std::next(misc::position_append_and_move(
              ins, instr_iter,
              assembly_->load_build(cpu_->fp_reg(), slot,
                                    acc_reg->temp_get())));
          }
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

  void SpimCodegen::fragment_entry_exit_build(assem::ProcFrag& frag)
  {
    // Note that the order is reversed to what we want to obtain.

    // Save/restore callee save registers.
    free_callee_save(frag);

    // Implement the view shift.
    view_shift(frag);

    assem::Instrs& ins = frag.instrs_get();

    // Save/restore return address in temporary register
    temp::Temp ra_save;

    misc::prepend_and_move(ins,
                           assembly_->move_build(cpu_->return_reg(), ra_save));

    misc::append_and_move(ins,
                          assembly_->move_build(ra_save, cpu_->return_reg()));

    // Put frame allocation/deallocation markups
    auto frame_allocation_markup =
      new assem::Label("# Allocate frame", temp::Label("frame-allocation"));
    ins.insert(ins.begin(), frame_allocation_markup);

    auto frame_deallocation_markup =
      new assem::Label("# Deallocate frame", temp::Label("frame-deallocation"));
    ins.emplace_back(frame_deallocation_markup);

    // Make fragment entry, prepending a definition of all the
    // incoming (conventionaly defined) registers.

    temp::Label entry_label("tc_" + frag.label_get().string_get());
    assem::Instrs frag_entry(assembly_->label_build(entry_label));

    frag_entry.front()->def() += cpu_->argument_regs()
      + cpu_->callee_save_regs() + cpu_->special_regs() + cpu_->return_reg();

    misc::prepend_and_move(ins, frag_entry);

    // Jump to the return address, appending the sink that specifies
    // that some registers are really special and are not to be used
    // (e.g., $zero, $fp etc.). We also specify that callee save are
    // live at the end, so that the day we have dead code removal,
    // they won't be thrown away for lack of use.

    assem::Instrs frag_exit(assembly_->ret_build(cpu_->return_reg()));

    frag_exit.back()->use() += cpu_->special_regs() + cpu_->callee_save_regs();

    misc::append_and_move(ins, frag_exit);
  }

  void SpimCodegen::frame_build(assem::ProcFrag& frag) const
  {
    if (0 < frag.frame_get().get_current_frame_size())
      {
        assem::Instrs& ins = frag.instrs_get();

        // 1. Prologue.

        auto frame_allocation_slot = ins.label_find("frame-allocation");
        assertion(frame_allocation_slot != ins.end());

        // Reserve a space in frame to save the frame pointer.
        const frame::InFrame* fp_save = frag.frame_get().frame_alloc();

        // Save the frame pointer in frame
        frame_allocation_slot = std::next(misc::position_append_and_move(
          ins, frame_allocation_slot,
          store_inframe(fp_save, cpu_->fp_reg(), cpu_->sp_reg())));

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
        delete (*frame_allocation_slot);
        ins.erase(frame_allocation_slot);

        // 2. Epilogue.

        auto frame_deallocation_slot = ins.label_find("frame-deallocation");
        assertion(frame_deallocation_slot != ins.end());

        // Move the frame pointer to the stack pointer. (i.e. SP <= FP)
        frame_deallocation_slot = std::next(misc::position_append_and_move(
          ins, frame_deallocation_slot,
          assembly_->move_build(cpu_->fp_reg(), cpu_->sp_reg())));

        // We reload initial value of the frame pointer.
        frame_deallocation_slot = std::next(misc::position_append_and_move(
          ins, frame_deallocation_slot,
          load_inframe(fp_save, cpu_->fp_reg(), cpu_->fp_reg())));

        // Delete allocated slots in frame.
        delete fp_save;

        // Remove frame deallocation markup
        delete (*frame_deallocation_slot);
        ins.erase(frame_deallocation_slot);
      }
  }

  void SpimCodegen::rewrite_program(assem::ProcFrag& frag,
                                    const temp::temp_set_type& spilled,
                                    temp::temp_set_type& created_temps) const
  {
    // To be implemented at TC-9, when there are actual spills.
  }

} // namespace target::mips
