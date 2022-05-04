/**
 ** \file tree/label.hh
 ** \brief Intermediate representation: label.hh
 **/

#pragma once

#include <iosfwd>

#include <temp/fwd.hh>
#include <temp/label.hh>
#include <tree/stm.hh>

namespace tree
{
  class Label : public Stm
  {
  public:
    /// Build a node representing the label \a label.
    explicit Label(const temp::Label& label);

    /** \name Accessors.
     ** \{ */

    /// Label represented by the node.
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
    virtual StmVariant variant(const rStm& ref) override;

  private:
    /// The label.
    temp::Label label_;
  };

} // namespace tree

#include <tree/label.hxx>
