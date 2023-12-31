/**
 ** \file regalloc/regallocator.hh
 ** \brief regalloc::RegisterAllocator declaration.
 **/

#ifndef REGALLOC_REGALLOCATOR_HH
# define REGALLOC_REGALLOCATOR_HH

# include <temp/temp.hh>
# include <assem/fwd.hh>
# include <assem/visitor.hh>
# include <target/fwd.hh>
# include <misc/timer.hh>

namespace regalloc
{

  /// "Allocate-registers" functor.
  class RegisterAllocator
    : public assem::Visitor
  {
  public:
    typedef assem::Visitor super_type;
    using super_type::operator();
    /** \name Ctor & Dtor
     ** \{ */
  public:
    /// Construct a RegisterAllocator.
    RegisterAllocator(const target::Target& target,
                      const temp::TempMap& tempmap,
                      bool coalesce_p = true, bool trace_p = false);
    /** \} */

  public:
    /// Allocate registers.
    virtual void operator()(assem::ProcFrag& frag) override;
    /// The result.
    temp::TempMap allocation_get() const;
    /// The timer.
    const misc::timer& timer_get() const;

  private:
    /* \brief Remove useless moves i.e. each Move which have the same
       register as source and destination.  */
    void remove_useless_moves(assem::Instrs& instrs);

    /// The current target.
    const target::Target& target_;
    /// The allocation itself.
    temp::TempMap tempmap_;
    /// Shall we coalesce registers.
    bool coalesce_p_;
    /// Produce detailed logs on register allocation.
    bool trace_p_;
    /// Register allocation timer.
    misc::timer timer_;
  };

} // namespace regalloc

#endif // !REGALLOC_REGALLOCATOR_HH
