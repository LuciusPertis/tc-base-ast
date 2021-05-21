/**
 ** \file assem/comment.hh
 ** \brief Specialization of assem::Instr for comments source.
 */

#pragma once

#include <assem/instr.hh>

namespace assem
{
  class Comment : public Instr
  {
  public:
    Comment(const std::string& comment);

    std::ostream& dump(std::ostream& ostr) const override;
  }; // class Comment

} // namespace assem

#include <assem/comment.hxx>
