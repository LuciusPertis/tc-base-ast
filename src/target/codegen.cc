/**
 ** \file target/codegen.cc
 ** \brief Implementation of target::Codegen.
 */

#include <assem/comment.hh>
#include <misc/contract.hh>
#include <target/codegen.hh>

namespace target
{
  // Generate code.
  assem::Instrs& Codegen::codegen(const tree::rStm& stm, frame::Frame& frame)
  {
    frame_ = &frame;
    instrs_.clear();
    assertion(instrs_.empty());
    codegen(stm);
    return instrs_;
  }

  void Codegen::trace(const std::string& rule)
  {
    if (rule_trace_p_)
      emit(new assem::Comment(std::string(indent_, ' ') + rule));
  }

  void Codegen::increase_indent() { indent_ += 2; }

  void Codegen::decrease_indent() { indent_ -= 2; }

} // namespace target
