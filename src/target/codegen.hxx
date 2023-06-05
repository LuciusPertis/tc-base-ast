/**
 ** \file target/codegen.hxx
 ** \brief Define the code generator mother class.
 */

#pragma once

#include <target/codegen.hh>

namespace target
{
  // Construct a Codegen.
  inline Codegen::Codegen(bool rule_trace_p)
    : frame_(nullptr)
    , rule_trace_p_(rule_trace_p)
  {}

  inline frame::Frame& Codegen::frame_get() { return *frame_; }

  inline assem::Instrs& Codegen::instrs_get() { return instrs_; }

  inline void Codegen::emit(assem::Instr* instr)
  {
    instrs_.emplace_back(instr);
  }

  inline void Codegen::emit(assem::Instrs instrs)
  {
    misc::append_and_move(instrs_, instrs);
  }

} // namespace target
