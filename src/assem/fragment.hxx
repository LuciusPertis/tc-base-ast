/**
 ** \file assem/fragment.hxx
 ** \brief Inline methods for assem/fragment.hh.
 */

#pragma once

#include <assem/fragment.hh>
#include <misc/contract.hh>

namespace assem
{
  /*-----------.
  | Fragment.  |
  `-----------*/

  inline std::ostream& operator<<(std::ostream& ostr, const Fragment& fragment)
  {
    return fragment.dump(ostr);
  }

  /*-----------.
  | DataFrag.  |
  `-----------*/

  inline DataFrag::DataFrag(const tree::DataFrag& frag)
    : data_frag_(frag)
  {}

  inline const tree::DataFrag& DataFrag::data_get() const { return data_frag_; }

  /*-----------.
  | ProcFrag.  |
  `-----------*/

  inline ProcFrag::ProcFrag(const tree::ProcFrag& frag)
    : frame_(frag.frame_get())
    , name_(frag.name_get())
    , label_(frag.label_get())
  {}

  inline frame::Frame& ProcFrag::frame_get() { return frame_; }

  inline const misc::symbol& ProcFrag::name_get() const { return name_; }

  inline temp::Label ProcFrag::label_get() const { return label_; }

  inline void ProcFrag::instrs_set(assem::Instrs& instrs)
  {
    precondition(instrs_.empty());
    std::swap(instrs_, instrs);
  }

  inline assem::Instrs& ProcFrag::instrs_get() { return instrs_; }

  inline const assem::Instrs& ProcFrag::instrs_get() const { return instrs_; }

} // namespace assem
