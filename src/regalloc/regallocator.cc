/**
 ** \file regalloc/regallocator.cc
 ** \brief regalloc::RegisterAllocator implementation.
 **/

#include <iostream>

#include <target/codegen.hh>
#include <regalloc/regallocator.hh>
#include <regalloc/color.hh>

namespace regalloc
{

  RegisterAllocator::RegisterAllocator(const target::Target& target,
                                       const temp::TempMap& tempmap,
                                       bool coalesce_p,
                                       bool trace_p)
    : target_(target)
    , tempmap_(tempmap)
    , coalesce_p_(coalesce_p)
    , trace_p_(trace_p)
  {
  }

  temp::TempMap
  RegisterAllocator::allocation_get() const
  {
    return tempmap_;
  }

  const misc::timer&
  RegisterAllocator::timer_get() const
  {
    return timer_;
  }

  /** \brief Predicate (object function) checking whether an
      instruction is a useless MOVE according to the TEMPMAP, and
      deleting it.

      Note that a better design would be to subclass std::list for
      list of pointers that ought to be deallocated, and then to
      specialize find_if to perform the delete itself.  */

  class UselessMove : public std::unary_function<assem::Instr, bool>
  {
  public:
    explicit UselessMove(const temp::TempMap& tempmap)
      : tempmap_(tempmap)
    {}

    bool
    operator()(const assem::Instr* instr) const
    {
      precondition(instr);
      bool res = false;
      auto move = dynamic_cast<const assem::Move*>(instr);
      if (move)
        res = tempmap_(move->def_get()) == tempmap_(move->use_get());
      if (res)
        delete instr;
      return res;
    }

  private:
    const temp::TempMap& tempmap_;
  };


  void
  RegisterAllocator::remove_useless_moves(assem::Instrs& instrs)
  {
  // FIXME: Some code was deleted here.
  }

  void
  RegisterAllocator::operator()(assem::ProcFrag& frag)
  {
    if (trace_p_)
      std::cerr << "## Register Allocation: start." << std::endl;
    for (;;)
      {
        Color color(frag, target_.cpu_get(), tempmap_,
                    coalesce_p_, trace_p_);
        bool succeeded = color();
        timer_ << color.timer_get();

        if (succeeded)
          {
            tempmap_.insert(color.tempmap_get());
            break;
          }

        // We failed to color: spill the potential spills.
        target_.codegen_get().rewrite_program(frag,
                                              color.spilled_get());

        if (trace_p_)
          {
            temp::Temp::map_type* om = &tempmap_;
            std::cerr << "## Instructions after spill:" << std::endl
                      << temp::Temp::map.swap(om)
                      << frag
                      << temp::Temp::map.swap(om)
                      << std::endl;
          }
      }
    if (trace_p_)
      std::cerr << "## Register Allocation: end." << std::endl;

    // Remove the useless moves.
    remove_useless_moves(frag.instrs_get());
  }

} // namespace regalloc
