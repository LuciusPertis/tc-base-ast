#include <iostream>
#include <memory> // unique_ptr

#include <assem/fwd.hh>
#include <target/arm/target.hh>
#include <target/cpu-limits.hh>
#include <target/libtarget.hh>
#include <tree/all.hh>
#include <tree/fragment.hh>

int main()
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
    new tree::ProcFrag(
      temp::Label("main"), "_main",
      new tree::Seq(new tree::Sxp(new tree::Call(
                      tree::rExp(new tree::Name(temp::Label("print"))),
                      std::vector<tree::rExp>{new tree::Name("l0")})),
                    new tree::Sxp(new tree::Const(0))),
      new frame::Frame("main"))};

  std::cout << hir_frags << '\n';

  target::arm::Target target;
  /* FIXME: Setting this frame::word_size global is ugly.  We shall
     get rid of it ASAP.  */
  frame::word_size = target.cpu_get().word_size_get();
  std::unique_ptr<assem::Fragments> assem_frags(
    target::lir_to_assem(hir_frags, target));

  target::instructions_dump(*assem_frags, target, std::cout);
}
