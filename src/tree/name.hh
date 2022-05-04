/**
 ** \file tree/name.hh
 ** \brief Intermediate representation: name.hh
 **/

#pragma once

#include <iosfwd>

#include <temp/label.hh>
#include <tree/exp.hh>
#include <tree/label.hh>

namespace tree
{
  class Name : public Exp
  {
  public:
    /// Build a reference to \a label.
    Name(const temp::Label& label);

    /** \name Accessors.
     ** \{ */

    /// Referenced label.
    temp::Label label_get() const;

    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream& ostr) const override;
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

    /// Iterating.
    void for_each_child(std::function<void(const rTree&)> f) override;

    /// Variant for matching.
    virtual ExpVariant variant(const rExp& ref) override;

  private:
    /// Referenced label.
    temp::Label label_;
  };

} // namespace tree

#include <tree/name.hxx>
