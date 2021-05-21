/**
 ** \file target/arm/arm-matcher.hh
 ** \brief Implementation of target::arm::ArmMatcher.
 **/

#include <target/arm/arm-matcher.hh>

#include <misc/lambda-visitor.hh>
#include <tree/tree-variants.hh>

namespace target::arm
{
  ArmMatcher::ArmMatcher(ArmCodegen* cg)
    : cg_(cg)
  {}

  void ArmMatcher::operator()(tree::rBinop binop)
  {
    auto left = binop->left_get()->variant(binop->left_get());
    auto right = binop->right_get()->variant(binop->right_get());

    tree::ExpVariant::visit(
      misc::LambdaVisitor{
        [&](auto lhs, tree::rConst cst) {
          TRACE("binop: Binop(exp, Const)");

          REDUCE(lhs);
          if (binop->oper_get() == tree::Binop::Oper::div)
            {
              temp::Temp arg1 = *MCPU.argument_regs().begin();
              temp::Temp arg2 = *std::next(MCPU.argument_regs().begin());

              EMIT(ASSEMBLY.move_build(lhs->asm_get(), arg1));
              EMIT(ASSEMBLY.move_build(cst->value_get(), arg2));

              temp::temp_list_type res(MCPU.caller_save_regs().begin(),
                                       MCPU.caller_save_regs().end());
              res.emplace_back(MCPU.result_reg());

              EMIT(ASSEMBLY.call_build("div", MCPU.argument_regs(), res));
              EMIT(ASSEMBLY.move_build(MCPU.result_reg(), binop->asm_get()));
            }
          else
            {
              EMIT(ASSEMBLY.binop_build(binop->oper_get(), lhs->asm_get(),
                                        cst->value_get(), binop->asm_get()));
            }
        },
        [&](auto lhs, auto rhs) {
          TRACE("binop: Binop(exp, exp)");

          REDUCE(lhs);
          REDUCE(rhs);

          if (binop->oper_get() == tree::Binop::Oper::div)
            {
              temp::Temp arg1 = *MCPU.argument_regs().begin();
              temp::Temp arg2 = *std::next(MCPU.argument_regs().begin());

              EMIT(ASSEMBLY.move_build(lhs->asm_get(), arg1));
              EMIT(ASSEMBLY.move_build(rhs->asm_get(), arg2));

              temp::temp_list_type res(MCPU.caller_save_regs().begin(),
                                       MCPU.caller_save_regs().end());
              res.emplace_back(MCPU.result_reg());

              EMIT(ASSEMBLY.call_build("div", MCPU.argument_regs(), res));
              EMIT(ASSEMBLY.move_build(MCPU.result_reg(), binop->asm_get()));
            }
          else
            {
              EMIT(ASSEMBLY.binop_build(binop->oper_get(), lhs->asm_get(),
                                        rhs->asm_get(), binop->asm_get()));
            }
        },
      },
      left, right);
  }

  void ArmMatcher::operator()(tree::rCall call)
  {
    TRACE("call: Call");

    auto func = call->func_get().cast<tree::Name>();
    auto args = call->args_get();

    auto args_it = args.begin();
    auto regs_it = MCPU.argument_regs().begin();

    for (; args_it != args.end() && regs_it != MCPU.argument_regs().end();
         args_it++, regs_it++)
      {
        REDUCE(*args_it);
        EMIT(ASSEMBLY.move_build((*args_it)->asm_get(), *regs_it));
      }

  // FIXME: Some code was deleted here (Store all the other arguments in frame).

    temp::temp_list_type res(MCPU.caller_save_regs().begin(),
                             MCPU.caller_save_regs().end());

    res.insert(res.begin(), MCPU.argument_regs().begin(),
               MCPU.argument_regs().end());
    res.emplace_back(MCPU.result_reg());

    EMIT(ASSEMBLY.call_build(func->label_get(), MCPU.argument_regs(), res));

    call->asm_set(MCPU.result_reg());
  }

  void ArmMatcher::operator()(tree::rConst cst)
  {
    TRACE("exp: Const");
    EMIT(ASSEMBLY.move_build(cst->value_get(), cst->asm_get()));
  }

  void ArmMatcher::operator()(tree::rMem mem)
  {
    auto var = mem->exp_get()->variant(mem->exp_get());

    var.visit(misc::LambdaVisitor{
      [&](tree::rBinop binop) {
        tree::rTree move =
          new tree::Move(new tree::Temp(mem->asm_get()), new tree::Mem(binop));

        auto left = binop->left_get();
        auto right = binop->right_get();

        if (left.is_a<tree::Const>())
          {
            TRACE("mem: Mem(Binop(Const, exp))");
            REDUCE(right);
            right->reducible_set(false);
          }
        else if (right.is_a<tree::Const>())
          {
            TRACE("mem: Mem(Binop(exp, Const))");
            REDUCE(left);
            left->reducible_set(false);
          }
        else
          {
            TRACE("mem: Mem(Binop(exp, exp))");
            REDUCE(left);
            REDUCE(right);
            left->reducible_set(false);
            right->reducible_set(false);
          }

        REDUCE(move);

        if (!left.is_a<tree::Const>())
          left->reducible_set(true);
        if (!right.is_a<tree::Const>())
          right->reducible_set(true);
      },
      [&](tree::rConst cst) {
        TRACE("mem: Mem(Const)");
        EMIT(ASSEMBLY.load_build(cst->value_get(), mem->asm_get()));
      },
      [&](auto exp) {
        TRACE("mem: Mem(exp)");
        REDUCE(exp);

        temp::Temp res;

        EMIT(ASSEMBLY.load_build(exp->asm_get(), res));
        mem->asm_set(res);
      },
    });
  }

  void ArmMatcher::operator()(tree::rName name)
  {
    TRACE("exp: Name");
    EMIT(ASSEMBLY.move_build(name->label_get(), name->asm_get()));
  }

  void ArmMatcher::operator()(tree::rTemp temp)
  {
    TRACE("temp: Temp");
    temp->asm_set(temp->temp_get());
  }

  void ArmMatcher::operator()(tree::rCjump cjump)
  {
    auto left = cjump->left_get()->variant(cjump->left_get());
    auto right = cjump->right_get()->variant(cjump->right_get());

    tree::ExpVariant::visit(
      misc::LambdaVisitor{
        // Note: this first case is superfluous, but we need it to compile.
        // Otherwise, the 2nd and 3rd visitor would be considered to match the
        // same cases, so we must explicitely take into account the case
        // with 2 constants.
        [&](tree::rConst exp, tree::rConst cst) {
          TRACE("cjump: Cjump(Const, Const)");

          REDUCE(exp);
          EMIT(ASSEMBLY.cjump_build(cjump->relop_get(), exp->asm_get(),
                                    cst->value_get(), cjump->label_true_get(),
                                    cjump->label_false_get()));
        },
        [&](auto exp, tree::rConst cst) {
          TRACE("cjump: Cjump(exp, Const)");

          REDUCE(exp);
          EMIT(ASSEMBLY.cjump_build(cjump->relop_get(), exp->asm_get(),
                                    cst->value_get(), cjump->label_true_get(),
                                    cjump->label_false_get()));
        },
        [&](tree::rConst cst, auto exp) {
          TRACE("cjump: Cjump(Const, exp)");

          REDUCE(exp);
          EMIT(ASSEMBLY.cjump_build(cjump->relop_get(), cst->value_get(),
                                    exp->asm_get(), cjump->label_true_get(),
                                    cjump->label_false_get()));
        },
        [&](auto e1, auto e2) {
          TRACE("cjump: Cjump(exp, exp)");

          REDUCE(e1);
          REDUCE(e2);
          EMIT(ASSEMBLY.cjump_build(cjump->relop_get(), e1->asm_get(),
                                    e2->asm_get(), cjump->label_true_get(),
                                    cjump->label_false_get()));
        },
      },
      left, right);
  }

  void ArmMatcher::operator()(tree::rJump jump)
  {
    TRACE("stm: Jump");

    temp::Label dest = jump->label_get().front();
    EMIT(ASSEMBLY.jump_build(dest));
  }

  void ArmMatcher::operator()(tree::rLabel label)
  {
    TRACE("stm: Label");
    EMIT(ASSEMBLY.label_build(label->label_get()));
  }

  void ArmMatcher::move_load(tree::rExp exp, tree::rBinop binop)
  {
    REDUCE(exp);

    if (binop->left_get().is_a<tree::Const>()
        || binop->right_get().is_a<tree::Const>())
      {
        precondition(binop->oper_get() == tree::Binop::Oper::sub
                     || binop->oper_get() == tree::Binop::Oper::add);

        short sign = 1;
        if (binop->oper_get() == tree::Binop::Oper::sub)
          sign = -1;

        if (auto cst_left = binop->left_get().unsafe_cast<tree::Const>())
          {
            REDUCE(binop->right_get());
            EMIT(ASSEMBLY.load_build(binop->right_get()->asm_get(),
                                     sign * cst_left->value_get(),
                                     exp->asm_get()));
          }
        else
          {
            auto cst_right = binop->right_get().unsafe_cast<tree::Const>();
            REDUCE(binop->left_get());
            EMIT(ASSEMBLY.load_build(binop->left_get()->asm_get(),
                                     sign * cst_right->value_get(),
                                     exp->asm_get()));
          }
      }
    else
      {
        REDUCE(binop);
        EMIT(ASSEMBLY.load_build(binop->asm_get(), exp->asm_get()));
      }
  }

  void ArmMatcher::move_store(tree::rExp exp, tree::rBinop binop)
  {
    REDUCE(exp);

    if (binop->left_get().is_a<tree::Const>()
        || binop->right_get().is_a<tree::Const>())
      {
        precondition(binop->oper_get() == tree::Binop::Oper::sub
                     || binop->oper_get() == tree::Binop::Oper::add);

        short sign = 1;
        if (binop->oper_get() == tree::Binop::Oper::sub)
          sign = -1;

        auto left = binop->left_get();
        auto right = binop->right_get();
        if (left.is_a<tree::Const>())
          {
            REDUCE(binop->right_get());
          }
        else
          {
            REDUCE(binop->left_get());
            left.swap(right);
          }

        auto cst_left = left.cast<tree::Const>();

        EMIT(ASSEMBLY.store_build(exp->asm_get(), right->asm_get(),
                                  sign * cst_left->value_get()));
      }
    else
      {
        REDUCE(binop);
        EMIT(ASSEMBLY.store_build(exp->asm_get(), binop->asm_get()));
      }
  }

  void ArmMatcher::operator()(tree::rMove move)
  {
    auto dst = move->dst_get()->variant(move->dst_get());
    auto src = move->src_get()->variant(move->src_get());

    tree::ExpVariant::visit(
      misc::LambdaVisitor{
        [&](tree::rMem mem1, tree::rMem mem2) {
          TRACE("move: Move(Mem(exp), Mem(exp))");

          temp::Temp rval;

          auto exp = mem2->exp_get();
          assertion(exp);
          REDUCE(exp);
          EMIT(ASSEMBLY.load_build(exp->asm_get(), rval));

          exp = mem1->exp_get();
          assertion(exp);
          REDUCE(exp);
          EMIT(ASSEMBLY.store_build(rval, exp->asm_get()));
        },
        [&](auto exp, tree::rMem mem) {
          TRACE("move: Move(exp, Mem(b : Binop(exp, exp)))");

          precondition(mem->exp_get().is_a<tree::Binop>());
          move_load(exp, mem->exp_get().cast<tree::Binop>());
        },
        [&](tree::rMem mem, auto exp) {
          if (auto binop = mem->exp_get().unsafe_cast<tree::Binop>())
            {
              TRACE("move: Move(Mem(b : Binop(exp, exp)), exp)");
              move_store(exp, binop);
            }
          else
            {
              if (auto cst = mem->exp_get().unsafe_cast<tree::Const>())
                {
                  TRACE("move: Move(Mem(Const), exp)");
  // FIXME: Some code was deleted here.
                }
              else
                {
                  TRACE("move: Move(Mem(exp), exp)");
                  REDUCE(mem->exp_get());
                  REDUCE(exp);
                  EMIT(ASSEMBLY.store_build(exp->asm_get(),
                                            mem->exp_get()->asm_get()));
                }
            }
        },
        [&](tree::rTemp temp, tree::rCall call) {
          TRACE("move: Move(temp, call)");
          REDUCE(temp);
          REDUCE(call);
          EMIT(ASSEMBLY.move_build(call->asm_get(), temp->asm_get()));
        },
        [&](tree::rTemp temp, tree::rConst cst) {
          TRACE("move: Move(temp, Const)");
          REDUCE(temp);
          EMIT(ASSEMBLY.move_build(cst->value_get(), temp->asm_get()));
        },
        [&](tree::rTemp temp, tree::rMem mem) {
          // This case is not caught by (auto, mem) since the dispatch is
          // solely based on types, and auto represents a default case.
          if (auto binop = mem->exp_get().unsafe_cast<tree::Binop>())
            {
              TRACE("move: Move(temp, Mem(b : Binop(exp, exp)))");
              move_load(temp, binop);
            }
          else
            {
              if (auto cst = mem->exp_get().unsafe_cast<tree::Const>())
                {
                  TRACE("move: Move(temp, Mem(Const))");
                  REDUCE(temp);
                  EMIT(ASSEMBLY.load_build(cst->value_get(), temp->asm_get()));
                }
              else
                {
                  TRACE("move: Move(temp, Mem(exp))");
                  REDUCE(temp);
                  REDUCE(mem->exp_get());
                  EMIT(ASSEMBLY.load_build(mem->exp_get()->asm_get(),
                                           temp->asm_get()));
                }
            }
        },
        [&](tree::rTemp temp, auto exp) {
          TRACE("move: Move(temp, exp)");
  // FIXME: Some code was deleted here.
        },
        [&](auto, auto) {
          unreachable(); // dst is necessarily a temp or a mem
        },
      },
      dst, src);
  }

  void ArmMatcher::operator()(tree::rSeq seq)
  {
    TRACE("stm: Seq");

    tree::tree_list_type& children = seq->children_get();
    for (auto c : children)
      REDUCE(c);
  }

  void ArmMatcher::operator()(tree::rSxp sxp)
  {
    TRACE("stm: Sxp(exp)");
    REDUCE(sxp->exp_get());
  }

} // namespace target::arm
