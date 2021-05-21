// -*- C++ -*-

%module tiger_target

%include "std_string.i"

%{
#  include <fstream>

#  include <target/target.hh>
#  include <target/cpu-limits.hh>
#  include <target/mips/target.hh>
#  include <target/ia32/target.hh>
#  include <target/arm/target.hh>
#  include <target/cpu.hh>
#  include <target/mips/cpu.hh>
#  include <target/ia32/cpu.hh>
#  include <target/arm/cpu.hh>
#  include <target/libtarget.hh>
%}

// Ignore C++11 `override' attributes, not understood by SWIG 2.
#define override

%include "target/fwd.hh"

%include "target/target.hh"
%include "target/cpu-limits.hh"

%rename(MipsTarget) target::mips::Target;
%rename(Ia32Target) target::ia32::Target;
%rename(ArmTarget) target::arm::Target;
%include "target/mips/target.hh"
%include "target/ia32/target.hh"
%include "target/arm/target.hh"

%include "target/cpu.hh"

%rename(MipsCpu) target::mips::Cpu;
%rename(Ia32Cpu) target::ia32::Cpu;
%rename(ArmCpu) target::arm::Cpu;
%include "target/mips/cpu.hh"
%include "target/ia32/cpu.hh"
%include "target/arm/cpu.hh"

%include "target/libtarget.hh"
