/**
 ** \file tree/temp.hh
 ** \brief Declaration of tree::Temp.
 **/

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <temp/temp.hh>
#include <tree/exp.hh>

namespace tree
{
  /// An Exp for a temporary (pseudo register).
  class Temp : public Exp
  {
  public:
    /// Build a node representing the temporary \a temp.
    explicit Temp(const temp::Temp& temp);

    /** \name Accessors.
     ** \{ */

    /// Pseudo register.
    temp::Temp temp_get() const;

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
    /// Pseudo register.
    temp::Temp temp_;
  };

} // namespace tree

#include <tree/temp.hxx>
