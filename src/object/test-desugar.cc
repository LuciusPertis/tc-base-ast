/// Checking the removal of object constructs.

#include <cstdlib>
#include <iostream>

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <ast/libast.hh>
#include <bind/libbind.hh>
#include <object/desugar-visitor.hh>
#include <object/libobject.hh>
#include <parse/libparse.hh>
#include <type/libtype.hh>

const char* program_name = "test-desugar";
const char* test_1 =
  R"( let
   type A = class
   {
     var s := "Hello"
     method m() = ()
   }

   var a : A := new A
 in
   a.s;
   a.m()
 end)";

const char* test_2 =
  R"( let
   primitive print(s : string)

   class A
   {
     var s := "Hello"
     method m() = (print(self.s); print("\n"))
   }
   class B extends A
   {
     var s2 := " World!"
     method m() = (print(self.s); print(self.s2);
                   print("\n"))
   }

   var b : B := new B
   var a : A := b
   var a2 : A := new B
 in
   b.m();
   a.m();
   a2.m();
   a := a2;
   a := b
 end)";

const char* test_3 =
  R"( let
   class A {}
   class B extends A {}
   function id(a : A) : A = a
   var b := new B
   var a := id(b)
 in
 end)";

int main() { std::cout << "/* Test 1.  */\n"; }
