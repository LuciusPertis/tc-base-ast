/**
 ** \file target/codegen.hxx
 ** \brief Define the code generator mother class.
 */

#ifndef TARGET_CODEGEN_HXX
# define TARGET_CODEGEN_HXX

# include <target/codegen.hh>

namespace target
{

  // Construct a Codegen.
  inline
  Codegen::Codegen(bool rule_trace_p)
    : frame_(nullptr)
    , rule_trace_p_(rule_trace_p)
  {
  }

  inline
  frame::Frame&
  Codegen::frame_get()
  {
    return *frame_;
  }

  inline
  assem::Instrs&
  Codegen::instrs_get()
  {
    return instrs_;
  }

  inline
  void
  Codegen::emit(assem::Instr* instr)
  {
    instrs_.push_back(instr);
  }

  inline
  void
  Codegen::emit(assem::Instrs instrs)
  {
    instrs_.splice(instrs_.end(), instrs);
  }

} // namespace target

#endif // !TARGET_CODEGEN_HXX
