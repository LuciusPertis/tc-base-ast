#!/bin/sh

[ -z "$1" ] && echo "$0: Missing input file" && exit
[ -z "$2" ] && echo "$0: Missing output file" && exit

input=$1
output=$2

awk 'BEGIN {
      print("#include \"target/mips/spim-assembly.hh\"");
      print("");
      print("namespace target {");
      print("namespace mips {");
      print("const char* SpimAssembly::runtime(bool) const");
      print("{");
      print("  return");
      printf("R\"(");
    }
    /^#(<<|>>)/ {
      next;
    }
    {
      print($0);
    }
    END {
      print(")\";");
      print("}");
      print("} // namespace mips");
      print("} // namespace target");
      print("");
    }' "$input" > "$output".tmp

mv "$output".tmp "$output"
