// Exercise register allocation.

#include <ostream>

#include <liveness/flowgraph.hh>
#include <liveness/interference-graph.hh>
#include <regalloc/regallocator.hh>
#include <target/cpu.hh>
#include <target/mips/spim-assembly.hh>
#include <target/mips/spim-codegen.hh>
#include <target/target.hh>
#include <tree/const.hh>
#include <tree/sxp.hh>

// A simple Cpu with three general-purpose registers.
class MyCpu : public target::Cpu
{
public:
  MyCpu()
  {
    caller_save_reg("r1");
    caller_save_reg("r2");

    callee_save_reg("r3");
  }

  size_t word_size_get() const override { return 4; }

  const temp::Temp& fp_reg() const override
  {
    static const temp::Temp fp("fp");
    return fp;
  }

  const temp::Temp& result_reg() const override
  {
    static const temp::Temp result("r1");
    return result;
  }
};

// A simple MIPS-based target using MyCpu.
class MyTarget : public target::Target
{
public:
  MyTarget(bool rule_trace_p = false)
    : codegen_(rule_trace_p)
  {
    // codegen_.cpu_set(cpu_);
    codegen_.assembly_set(assembly_);
  }

  const target::Cpu& cpu_get() const override { return cpu_; }
  target::Cpu& cpu_get() override { return cpu_; }

  const target::Assembly& assembly_get() const override { return assembly_; }
  target::Assembly& assembly_get() override { return assembly_; }

  const target::Codegen& codegen_get() const override { return codegen_; }
  target::Codegen& codegen_get() override { return codegen_; }

protected:
  MyCpu cpu_;
  target::mips::SpimCodegen codegen_;
  target::mips::SpimAssembly assembly_;
};

using Ts = temp::temp_list_type;
using Ls = temp::label_list_type;

/* This is the example used by Andrew Appel in Chapter 10 of his
   ``Modern Compiler Implementation'' books.  */
static void example_1()
{
  temp::Temp a("a");
  temp::Temp b("b");
  temp::Temp c("c");

  temp::Label l1("L1");
  temp::Label lreturn("Lreturn");

  assem::Instrs instrs = {
    /* Dummy node to define `c', so that the construction of the
       liveness graph won't complain about this register not being
       defined. */
    new assem::Oper("", Ts(), Ts(c)),

    // a := 0
    new assem::Oper("a := 0", Ts(), Ts(a)),

    // L1: b := a + 1
    new assem::Label("L1:", l1), new assem::Oper("b := a + 1", Ts(a), Ts(b)),

    // c := c + b
    new assem::Oper("c := c + b", Ts(c, b), Ts(c)),

    // a := b * 2
    new assem::Oper("a := b * 2", Ts(b), Ts(a)),

    // a < N
    /* Note that we had to insert an explicit jump to a label
       `Lreturn' (for the false case), which is implicit in the
       original code.  */
    new assem::Oper("a < N", Ts(a), Ts(), Ls(l1, lreturn)),

    // return c
    new assem::Label("Lreturn:", lreturn),
    new assem::Oper("return c", Ts(c), Ts())};

  std::cout << "Example 1\n"
            << "---------\n";

  instrs.dump(std::cout);
  std::cout << "\n";

  liveness::FlowGraph<> fg("Flow Graph #1", instrs);
  fg.print(std::cout);
  std::cout << "\n";

  temp::TempMap tempmap;
  liveness::InterferenceGraph ig("Interference Graph #1", instrs, tempmap);
  ig.print(std::cout);
  std::cout << "\n";

  // Dummy tree::ProcFrag.
  temp::Label proc_label("lexample1");
  misc::symbol proc_name("example1");
  tree::rStm proc_body(new tree::Sxp(new tree::Const(0)));
  auto proc_frame = new frame::Frame(proc_label);
  tree::ProcFrag tree_procfrag(proc_label, proc_name, proc_body, proc_frame);

  assem::ProcFrag assem_procfrag(tree_procfrag);
  assem_procfrag.instrs_set(instrs);
  MyTarget target;
  regalloc::RegisterAllocator allocator(target, tempmap);
  allocator(assem_procfrag);
  std::cout << allocator.allocation_get() << '\n';
}

/* Example 11.8 from Andrew Appel's ``Modern Compiler Implementation''
   books.  */
static void example_2()
{
  temp::Temp a("a");
  temp::Temp b("b");
  temp::Temp c("c");
  temp::Temp d("d");
  temp::Temp e("e");
  temp::Temp r1("r1");
  temp::Temp r2("r2");
  temp::Temp r3("r3");

  temp::Label loop("loop");
  temp::Label end("end");

  assem::Instrs instrs = {

    // Dummy node to define the machine registers (`r1', `r2' and `r3').
    new assem::Oper("", Ts(), Ts{r1, r2, r3}),

    // c := r3
    new assem::Move("c := r3", r3, c),

    // a := r1
    new assem::Move("a := r1", r1, a),

    // b := r2
    new assem::Move("b := r2", r2, b),

    // d := 0
    new assem::Oper("d := 0", Ts(), Ts(d)),

    // e := a
    new assem::Move("e := a", a, e),

    // loop: d := d + b
    new assem::Label("loop:", loop),
    new assem::Oper("d := d + b", Ts(d, b), Ts(d)),

    // e := e - 1
    new assem::Oper("e := e - 1", Ts(e), Ts(e)),

    // if e > 0 goto loop
    /* Note that we had to insert an explicit jump to a label
       `end' (for the false case), which is implicit in the
       original code.  */
    new assem::Oper("if e > 0 goto loop", Ts(e), Ts(), Ls(loop, end)),

    // r1 := d
    new assem::Label("end:", end), new assem::Move("r1 := d", d, r1),

    // r3 := c
    new assem::Move("r3 := c", c, r3),

    // return
    new assem::Oper("return",
                    // We ``use'' r1 and r3 here, as they are live out.
                    Ts(r1, r3), Ts())};

  std::cout << "Example 2\n"
            << "---------\n";

  instrs.dump(std::cout);
  std::cout << "\n";

  liveness::FlowGraph<> fg("Flow Graph #2", instrs);
  fg.print(std::cout);
  std::cout << "\n";

  temp::TempMap tempmap;
  liveness::InterferenceGraph ig("Interference Graph #2", instrs, tempmap);
  ig.print(std::cout);
  std::cout << "\n";

  /* TODO: Run the register allocator on this interference graph.

     Note that the strategy used at the end of example_1() does not
     work here (as-is): the register allocator causes a SIGSEGV when
     rewriting the program after an actual spill, probably because of
     the dummy boilerplate used to instanciate
     regalloc::RegisterAllocator.  */
}

int main()
{
  example_1();
  example_2();
}
