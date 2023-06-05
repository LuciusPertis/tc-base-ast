#!/bin/sh

[ -z "$1" ] && echo "$0: Missing input file" && exit
[ -z "$2" ] && echo "$0: Missing output file" && exit

input=$1
output=$2

awk 'BEGIN {
      print("#include \"target/ia32/gas-assembly.hh\"");
      print("");
      print("namespace target {");
      print("namespace ia32 {");
      print("const char* GasAssembly::runtime(bool gc) const");
      print("{");
      print("  if (!gc)");
      print("    return");
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
    }' "$input" > "$output".tmp

awk 'BEGIN {
      print("  else");
      print("    return");
      printf("R\"(");
    }
    /^#(<<|>>)/ {
      next;
    }
    {
      gsub(/call[ \t]+malloc/, "call\tGC_malloc", $0);
      print($0);
    }
    END {
      print(")\";");
      print("}");
      print("} // namespace ia32");
      print("} // namespace target");
      print("");
    }' "$input" >> "$output".tmp

mv "$output".tmp "$output"
