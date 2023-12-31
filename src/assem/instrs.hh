/**
 ** \file assem/instrs.hh
 ** \brief Declaration of assem::Instrs.
 */

#ifndef ASSEM_INSTRS_HH
# define ASSEM_INSTRS_HH

# include <iosfwd>
# include <list>

# include <assem/fwd.hh>

namespace assem
{

  /* FIXME: assem::Instrs shall not derive from std::list.  This class
     has only move semantics, whereas std::list has both move *and*
     copy semantics.  This is a form of inheritance by restriction,
     which is usually bad practice.  */

  /// List of Instr.
  ///
  /// This class has move semantics only: it cannot be copied through
  /// construction nor assignment.
  class Instrs : public std::list<Instr*>
  {
  public:
    /// Super class.
    typedef std::list<Instr*> super_type;

    Instrs() = default;
    Instrs(std::initializer_list<Instr*> l);

    /// \name Disable copy construction and assignment.
    /// \{
    Instrs(const Instrs&) = delete;
    Instrs& operator=(const Instrs&) = delete;
    /// \}

    /// \name Allow move construction and assignment.
    /// \{
    Instrs(Instrs&&) = default;
    Instrs& operator=(Instrs&&) = default;
    /// \}

    virtual ~Instrs();

    /// (Explicit)
    iterator label_find(const temp::Label &l);

    /// Report the instructions on \a ostr.
    virtual std::ostream& dump(std::ostream& ostr) const;
  };

  /// Output \a instrs on \a ostr;
  std::ostream&
  operator<< (std::ostream& ostr, const Instrs& instrs);

} // namespace assem

#endif // !ASSEM_INSTRS_HH
