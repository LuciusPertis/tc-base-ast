namespace target
{

  namespace arm
  {

    // Current codegen object running monoburg.
    ArmCodegen *cg;

    ArmCodegen::ArmCodegen(bool rule_trace_p)
      : target::Codegen(rule_trace_p)
      , cpu_(nullptr)
      , assembly_(nullptr)
    {}

    void
    ArmCodegen::cpu_set(const target::arm::Cpu& cpu)
    {
      cpu_ = &cpu;
    }

    inline
    const target::arm::Cpu*
    ArmCodegen::cpu_get() const
    {
      return cpu_;
    }

    void
    ArmCodegen::assembly_set(ArmAssembly& assembly)
    {
      assembly_ = &assembly;
    }

    ArmAssembly&
    ArmCodegen::assembly_get()
    {
      assertion(assembly_);
      return *assembly_;
    }

    void
    ArmCodegen::codegen(const tree::rStm& root)
    {
      assertion(cpu_);
      tree::rTree root_ = root.cast<Tree>();

      cg = this;
      reduce(root_, MB_NTERM_stm);
    }

    void
    ArmCodegen::reduce(rTree& tree, int goal)
    {
      static int indent_ = -2;
      rTree* kids[10];
      int ern;
      const guint16* nts;

      if (not tree->reducible_get())
        return;

      indent_ += 2;
      mono_burg_label(&tree, nullptr);

      ern = mono_burg_rule(static_cast<MBState*>(tree->state_get()), goal);
      nts = mono_burg_nts[ern];

      if (rule_trace_p_)
        emit(new assem::Comment(std::string(indent_, ' ')
             + mono_burg_rule_string[ern]));

      mono_burg_kids(&tree, ern, kids);

      for (int i = 0; nts[i]; ++i)
        reduce(*(kids[i]), nts [i]);

      if (mono_burg_func[ern])
        mono_burg_func[ern](tree, nullptr);
      indent_ -= 2;
    }

    assem::Instrs
    ArmCodegen::store_inframe(const frame::Access* access,
                              const temp::Temp&    word,
                              const temp::Temp&    addr) const
    {
      auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
      return assembly_->store_build(word, addr, acc_frame.offset_get());
    }


    assem::Instrs
    ArmCodegen::load_inframe(const frame::Access*  access,
                             const temp::Temp&     word,
                             const temp::Temp&     addr) const
    {
      auto acc_frame = dynamic_cast<const frame::InFrame&>(*access);
      return assembly_->load_build(addr, acc_frame.offset_get(), word);
    }


    void
    ArmCodegen::free_callee_save(assem::ProcFrag& frag)
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


    void
    ArmCodegen::view_shift(assem::ProcFrag& frag)
    {
      // Access to current Frame.
      Frame& frame = frag.frame_get();

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
           ++formal_iter                 ,   ++arg_iter)
      {
        // A formal is either a InRegister (data is in a register) or
        // a InFrame (data is frame).
        auto acc_reg =
          dynamic_cast<const frame::InRegister*>(*formal_iter);

        if (acc_reg)
          // Formal type is InRegister.
          instr_iter =
            std::next(
              misc::position_append_and_move(
                ins, instr_iter, assembly_->move_build(*arg_iter,
                                                       acc_reg->temp_get())));
        else
          // Formal type is InFrame.
          instr_iter =
            std::next(
              misc::position_append_and_move(
                ins, instr_iter, store_inframe(*formal_iter, *arg_iter,
                                               cpu_->fp_reg())));
      }


      // Move all the other arguments from the frame to
      // their dedicated location.
      for (size_t slot = 3 * cpu_->word_size_get();
           formal_iter != formals.end(); ++formal_iter)
      {
        // A formal is either a InRegister (data is in a register) or
        // a InFrame (data is frame).
        auto acc_reg =
          dynamic_cast<const frame::InRegister*>(*formal_iter);

        if (acc_reg)
        {
          // Formal type is InRegister.
          // Load the argument from the frame.
          instr_iter =
            std::next(
              misc::position_append_and_move(
                ins, instr_iter, assembly_->load_build(cpu_->fp_reg(), slot,
                                                       acc_reg-> temp_get())));
        }
        else
        {
          // Formal type is InFrame.
          // Load the argument from the frame into a new temporary.
          temp::Temp temp;

          instr_iter =
            std::next(
              misc::position_append_and_move(
                ins, instr_iter, assembly_->load_build(cpu_->fp_reg(), slot,
                                                       temp)));

          // Store the temporary to his dedicated location (in frame).
          instr_iter =
            std::next(
              misc::position_append_and_move(
                ins, instr_iter, store_inframe(*formal_iter, temp,
                                                cpu_->fp_reg())));
        }
        slot += cpu_->word_size_get();
      }
    }


    void
    ArmCodegen::fragment_entry_exit_build(assem::ProcFrag& frag)
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
        new assem::Label("# Allocate frame",
            temp::Label("frame-allocation"));
      ins.emplace(ins.begin(), frame_allocation_markup);

      auto frame_deallocation_markup =
        new assem::Label("# Deallocate frame",
            temp::Label("frame-deallocation"));
      ins.emplace_back(frame_deallocation_markup);

      // Make fragment entry, prepending a definition of all the incoming
      // (conventionaly defined) registers.

      temp::Label entry_label("tc_" + frag.label_get().string_get());
      assem::Instrs frag_entry(assembly_->label_build(entry_label));

      frag_entry.front()->def() += cpu_->argument_regs()
                                 + cpu_->callee_save_regs()
                                 + cpu_->special_regs();

      misc::prepend_and_move(ins, frag_entry);

      // Append the sink that specifies that some registers are really
      // special and are not to be used (e.g., $zero, $fp etc.).  We
      // also specify that callee save are live at the end, so that
      // the day we have dead code removal, they won't be thrown away
      // for lack of use.
      assem::Instrs frag_exit(assembly_->ret_build());
      frag_exit.back()->use() += cpu_->special_regs()
                               + cpu_->callee_save_regs();

      misc::append_and_move(ins, frag_exit);
    }

    void
    ArmCodegen::frame_build(assem::ProcFrag& frag) const
    {
     assem::Instrs& ins = frag.instrs_get();

      // 1. Prologue.

      auto frame_allocation_slot = ins.label_find("frame-allocation");
      assertion(frame_allocation_slot != ins.end());

      // Save the frame pointer in frame
      frame_allocation_slot =
        std::next(
          misc::position_append_and_move(
            ins, frame_allocation_slot, assembly_->push_build(cpu_->fp_reg(),
                                                              cpu_->lr_reg())));

      // Counter the pre-dec/post-incrementation effect
      frame_allocation_slot =
        std::next(
          misc::position_append_and_move(
            ins, frame_allocation_slot,
            assembly_->binop_build(Binop::sub, cpu_->sp_reg(),
                                   cpu_->word_size_get(),
                                   cpu_->fp_reg())));

      // Allocate the frame by decrementing the stack pointer.
      frame_allocation_slot =
        std::next(
          misc::position_append_and_move(
            ins, frame_allocation_slot,
            assembly_->binop_build(Binop::sub, cpu_->sp_reg(),
                                   frag.frame_get().get_current_frame_size(),
                                   cpu_->sp_reg())));

      // Remove frame allocation markup
      delete *frame_allocation_slot;
      ins.erase(frame_allocation_slot);

      // 2. Epilogue.

      auto frame_deallocation_slot = ins.label_find("frame-deallocation");
      assertion(frame_deallocation_slot != ins.end());

      // Prepare frame restoration
      frame_deallocation_slot =
        std::next(
          misc::position_append_and_move(
            ins, frame_deallocation_slot,
            assembly_->binop_build(Binop::add, cpu_->sp_reg(),
                                   frag.frame_get().get_current_frame_size(),
                                   cpu_->sp_reg())));

      // Remove frame deallocation markup
      delete *frame_deallocation_slot;
      ins.erase(frame_deallocation_slot);
    }

    void
    ArmCodegen::rewrite_program(assem::ProcFrag& frag,
                                const temp::temp_set_type& spilled) const
    {
  // FIXME: Some code was deleted here (Needed in TC-9, when there are actual spills).
    }

  } // namespace arm

} // namespace target
