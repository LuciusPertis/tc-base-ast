/**
 ** \file assem/move.hxx
 ** \brief Inline methods for assem/move.hh.
 */

#ifndef ASSEM_MOVE_HXX
# define ASSEM_MOVE_HXX

# include <misc/contract.hh>
# include <assem/move.hh>

namespace assem
{
  typedef temp::temp_list_type L;

  inline
  Move::Move(const std::string& assem,
             const temp::Temp& used_temps,
             const temp::Temp& defd_temps)
    : Instr(assem, L(used_temps), L(defd_temps))
  {
  }

  inline temp::Temp
  Move::dst_get() const
  {
    return def().front();
  }

  inline temp::Temp
  Move::src_get() const
  {
    return use().front();
  }

  inline temp::Temp
  Move::use_get() const
  {
    precondition(use_.size() == 1);
    return use_.front();
  }

  inline temp::Temp
  Move::def_get() const
  {
    precondition(def_.size() == 1);
    return def_.front();
  }

  inline std::ostream&
  Move::dump(std::ostream& ostr) const
  {
    ostr << '\t';
    return Instr::dump(ostr);
  }

} // namespace assem

#endif // !ASSEM_MOVE_HXX
