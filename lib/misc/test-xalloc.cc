/**
 ** Test code for misc/xalloc.hh features.
 */

#include <iostream>
#include <sstream>
#include <misc/xalloc.hh>
#include <misc/contract.hh>

struct my_unique_type {};
struct my_other_unique_type {};

int main()
{
  std::ostringstream s;
  int test = 1;
  int test_two = 42;
  int var = 0;

  typedef misc::xalloc<int> int_flag;
  const int_flag flag1, flag2;

  // Initially, should be 0 and 0.
  assertion(flag1(s) == 0);
  assertion(flag2(s) == 0);

  s << flag1.set(test);
  s << flag1.set(++test);
  // Var should be set to 2.
  var = flag1(s);

  s << flag1.set(++test) << var << std::endl;
  // Var should be set to 3.
  var = flag1(s);
  s << var << std::endl;

  s << flag1.set(++test);
  // Var should be set to 4.
  s << flag1.get(var);

  // Let's deal with another xalloc.
  s << flag2.set(test_two);
  // Test if var has not changed.
  s << var << std::endl;

  s << flag2.get(var);
  // Var == 42.
  s << var << std::endl;

  s << flag1.get(var);
  // Var == 4.
  s << var << std::endl;

  // Switch test
  int val = 43;
  s << flag1.swap(val);
  s << flag1.get(var);
  // Var should be set to 43
  s << var << std::endl;
  s << flag1.swap(val);
  s << flag1.get(var);
  // Var should be set to 4
  s << var << std::endl;
  // Is it reproductible ?
  ++val;
  s << flag1.swap(val);
  s << flag1.get(var);
  // Var should be set to 44
  s << var << std::endl;
  s << flag1.swap(val);
  s << flag1.get(var);
  // Var should be set to 4
  s << var << std::endl;

  std::string expected = "2\n3\n4\n42\n4\n43\n4\n44\n4\n";
  assertion(s.str() == expected);
}
