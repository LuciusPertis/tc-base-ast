/**
 ** \file assem/fragment.hh
 ** \brief Fragments of assembly.
 */

#pragma once

#include <tree/fragment.hh>

#include <assem/fwd.hh>
#include <assem/instrs.hh>
#include <temp/label.hh>

namespace assem
{
  /*-----------.
  | Fragment.  |
  `-----------*/

  /// Abstract a fragment in assembly language.
  class Fragment
  {
  public:
    virtual ~Fragment() = default;

    virtual std::ostream& dump(std::ostream& os) const = 0;

    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a Visitor \a v.
    virtual void accept(Visitor& v) = 0;
    virtual void accept(ConstVisitor& v) const = 0;
    /** \} */
  }; // class Fragment

  /// Report \a fragment on \a ostr.
  std::ostream& operator<<(std::ostream& ostr, const Fragment& fragment);

  /*-----------.
  | DataFrag.  |
  `-----------*/

  /// Encapsulate a data fragment in assembly language.
  class DataFrag : public Fragment
  {
  public:
    DataFrag(const tree::DataFrag& frag);

    std::ostream& dump(std::ostream& ostr) const override;

    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a Visitor \a v.
    void accept(Visitor& v) override;
    void accept(ConstVisitor& v) const override;
    /** \} */

  public:
    const tree::DataFrag& data_get() const;

  protected:
    tree::DataFrag data_frag_;
  };

  /*-----------.
  | ProcFrag.  |
  `-----------*/

  /// Encapsulate an instruction fragment in assembly language.
  class ProcFrag : public Fragment
  {
  public:
    ProcFrag(const tree::ProcFrag& frag);

    std::ostream& dump(std::ostream& ostr) const override;

    /// The frame.
    frame::Frame& frame_get();
    /// Original name of the function (for debugging).
    const misc::symbol& name_get() const;
    /// Unique label in the output.
    temp::Label label_get() const;
    /// A (unique) file name for this fragment.
    /// \param p  a prefix
    /// \param s  a suffix
    std::string file_name(const std::string& p = "",
                          const std::string& s = "") const;

    /// \brief Set the instructions of \a this to \a instrs.
    /// \warning: \a instrs is emptied, its content is stolen.
    void instrs_set(assem::Instrs& instrs);
    /// The instructions.
    assem::Instrs& instrs_get();
    /// The instructions.
    const assem::Instrs& instrs_get() const;

    /** \name Visitors entry point.
     ** \{ */
  public:
    /// Accept a Visitor \a v.
    void accept(Visitor& v) override;
    void accept(ConstVisitor& v) const override;
    /** \} */

  protected:
    /// The frame.
    frame::Frame frame_;
    /// Original name.
    const misc::symbol& name_;
    /// Unique label.
    temp::Label label_;
    /// Instructions computed by codegen.
    assem::Instrs instrs_;
  }; // class DataFrag

} // namespace assem

#include <assem/fragment.hxx>
