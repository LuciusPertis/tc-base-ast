/**
 ** \file target/target.hh
 ** \brief Abstract a Target machine.
 */

#ifndef TARGET_TARGET_HH
# define TARGET_TARGET_HH

# include <iosfwd>
# include <target/fwd.hh>

namespace target
{
  /// A Target is the union of a Cpu and a Codegen.
  class Target
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    virtual ~Target();
    /** \} */

    /** \name Accessors.
     ** \{ */
  public:
    virtual const Cpu& cpu_get() const = 0;
    virtual Cpu& cpu_get() = 0;

    virtual const Assembly& assembly_get() const = 0;
    virtual Assembly& assembly_get() = 0;

    virtual const Codegen& codegen_get() const = 0;
    virtual Codegen& codegen_get() = 0;
    /** \} */


    /// Description.
    std::ostream& dump(std::ostream& ostr) const;
  };

  /// Output \a t on \a ostr.
  std::ostream& operator<<(std::ostream& ostr, const Target& t);

} // namespace target

#endif // !TARGET_TARGET_HH
