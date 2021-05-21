/**
 ** \file target/libtarget.cc
 ** \brief Translating fragments from LIR to Assem.
 */

#include <assem/fragment.hh>
#include <assem/fragments.hh>
#include <assem/instr.hh>
#include <assem/layout.hh>
#include <misc/contract.hh>
#include <target/assembly.hh>
#include <target/codegen.hh>
#include <target/libtarget.hh>
#include <target/target.hh>
#include <tree/fragments.hh>
#include <tree/visitor.hh>

namespace target
{
  // Produce architecture-dependent assembly instructions.
  assem::Fragments* lir_to_assem(const tree::Fragments& frags, Target& target)
  {
    class ConvertVisitor : public tree::ConstVisitor
    {
    public:
      using tree::ConstVisitor::operator();

      ConvertVisitor(Codegen& gen)
        : fragments_(new assem::Fragments)
        , codegen_(gen)
      {}

      assem::Fragments* fragments_get() { return fragments_; }

      void operator()(const tree::ProcFrag& frag) override
      {
        // Build an assembly-instruction fragment.
        auto proc_frag = new assem::ProcFrag(frag);
        proc_frag->instrs_set(
          codegen_.codegen(frag.body_get(), proc_frag->frame_get()));
        // Move argument registers to their dedicated locations and
        // add Moves to save/restore callee save registers.
        codegen_.fragment_entry_exit_build(*proc_frag);
        fragments_->emplace_back(proc_frag);
      }

      void operator()(const tree::DataFrag& frag) override
      {
        // Build an assembly-data fragment.
        fragments_->emplace_back(new assem::DataFrag(frag));
      }

    private:
      assem::Fragments* fragments_;
      Codegen& codegen_;
    };

    ConvertVisitor visitor(target.codegen_get());
    visitor(frags);
    return visitor.fragments_get();
  }

  void runtime_dump(const Target& target, bool gc, std::ostream& str)
  {
    str << target.assembly_get().runtime(gc) << '\n';
  }

  void instructions_dump(assem::Fragments& fragments,
                         Target& target,
                         std::ostream& ostr)
  {
    // Setup target's assembly layout visitor.
    assem::Layout& layout = target.assembly_get().layout_get();
    layout.ostr_set(ostr);
    // Request for assembly fragments layout.
    layout(fragments);
  }

  void instructions_dump(assem::Fragments& fragments,
                         Target& target,
                         temp::TempMap& tempmap,
                         std::ostream& ostr,
                         bool instructions_debug_p)
  {
    temp::TempMap* map_ptr = &tempmap;
    ostr << assem::Instr::debug.swap(instructions_debug_p)
         << temp::Temp::map.swap(map_ptr);
    instructions_dump(fragments, target, ostr);
    ostr << assem::Instr::debug.swap(instructions_debug_p)
         << temp::Temp::map.swap(map_ptr);
  }

  /*-----------------.
  | frame_allocate.  |
  `-----------------*/

  void frame_allocate(assem::Fragments& fragments, const Target& target)
  {
    struct FrameAllocate : public assem::Visitor
    {
      using assem::Visitor::operator();
      FrameAllocate(const Codegen& gen)
        : codegen_(gen)
      {}

      void operator()(assem::ProcFrag& frag) override
      {
        codegen_.frame_build(frag);
      }
      const Codegen& codegen_;
    };

    FrameAllocate v(target.codegen_get());
    v(fragments);
  }

} // namespace target
