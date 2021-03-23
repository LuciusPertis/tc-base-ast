/**
 ** \file tree/const.hh
 ** \brief Intermediate representation: const.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/exp.hh>

namespace tree
{
  class Const : public Exp
  {
  public:
    /// Build a constant integer value.
    explicit Const(int value);

    /** \name Accessors.
     ** \{ */

    /// Return constant integer value.
    const int& value_get() const;

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
    const int value_;
  };

} // namespace tree

#include <tree/const.hxx>
