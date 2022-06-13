// -*- C++ -*-

%module tiger_target

%include "std_string.i"
%import "tiger_assem.i"

%{
  #include <fstream>

  #include <target/target.hh>
  #include <target/cpu-limits.hh>
  #include <target/mips/target.hh>
  #include <target/ia32/target.hh>
  #include <target/arm/target.hh>
  #include <target/cpu.hh>
  #include <target/mips/cpu.hh>
  #include <target/ia32/cpu.hh>
  #include <target/arm/cpu.hh>
  #include <target/libtarget.hh>
  using target::mips::SpimCodegen;
  using target::ia32::GasCodegen;
  using target::arm::ArmCodegen;
%}

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

%extend target::Target
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}

%extend target::Cpu
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}

%include "target/libtarget.hh"
