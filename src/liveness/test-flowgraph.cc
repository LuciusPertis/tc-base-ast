#include <ostream>
#include <assem/libassem.hh>
#include <liveness/flowgraph.hh>
#include <temp/label.hh>

using namespace assem;
using namespace liveness;

int main()
{
  temp::temp_list_type ts1;
  temp::temp_list_type ts2;

  temp::Label l1("l1");
  temp::Label l2("l2");
  temp::label_list_type ls(l1, l2);

  Instrs instrs = {
    new Oper("a := 0", ts2, ts1),     //   a := 0
    new Label("label l1", l1),        // label l1
    new Oper("b := a + 1", ts2, ts1), //   b := a + 1
    new Oper("a := b * 2", ts2, ts1), //   a := b * 2
    new Oper("c := c + b", ts2, ts1), //   c := c + b
    new Oper("a := b * 2", ts2, ts1), //   a := b * 2
    new Oper("a < N", ts1, ts2, ls),  //   a < N
    new Label("label l2", l2),        // label l2
    new Oper("return c", ts2, ts1)    //   return c
  };

  FlowGraph<misc::empty> flowgraph("test", instrs);

  flowgraph.print("test-flowgraph");
}
