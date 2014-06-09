#include <iostream>

#include <tree/fragment.hh>
#include <tree/all.hh>

#include <assem/fwd.hh>
#include <target/cpu-limits.hh>
#include <target/mips/target.hh>
#include <target/libtarget.hh>

int
main()
{
  // Build a small Tree program.
  //
  //   label l0
  //           "42\n"
  //   # Routine: _main
  //   label main
  //   # Prologue
  //   # Body
  //   seq
  //     sxp
  //       call
  //         name print
  //         name l0
  //       call end
  //     sxp
  //       const 0
  //   seq end
  //   # Epilogue
  //   label end
  tree::Fragments hir_frags = {
    new tree::DataFrag(temp::Label("l0"), "42\n"),
    new tree::ProcFrag
    (temp::Label("main"),
     "_main",
     new tree::Seq
     (new tree::Sxp(new tree::Call
                    (tree::rExp(new tree::Name(temp::Label("print"))),
                     std::list<tree::rExp> { new tree::Name("l0") })),
      new tree::Sxp(new tree::Const(0))),
     new frame::Frame ("main"))
  };

  std::cout << hir_frags << std::endl;

  target::CpuLimits limits;
  target::mips::Target target(limits);
  /* FIXME: Setting this frame::word_size global is ugly.  We shall
     get rid of it ASAP.  */
  frame::word_size = target.cpu_get().word_size_get();
  std::auto_ptr<assem::Fragments>
    assem_frags(target::lir_to_assem(hir_frags, target));

  /* Note that if we wanted to diplay Nolimips register names (`$x42')
     instead of temporary names (`t42'), we would need to use the
     5-argument version of target::instructions_dump and pass it the
     temp map returned by target.cpu_get().tempmap_get().clone().  As
     we don't really need it for this test, we use the simpler
     3-argument version of target::instructions_dump.  */
  target::instructions_dump(*assem_frags, target, std::cout);
}
