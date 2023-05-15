/**
 ** \file tree/seq.hh
 ** \brief Intermediate representation: seq.hh
 **/

#pragma once

#include <iosfwd>

#include <tree/stm.hh>

namespace tree
{
  class Seq : public Stm
  {
  public:
    /** \name Constructors.
     ** \{ */

    /// Construct using \a children as child statement list.
    Seq(const tree_list_type& children);

    /// Construct a statement list of two statements, \a left and \a right.
    Seq(const rStm& left, const rStm& right);

    /// Construct a statement list of one statement, \a left.
    Seq(const rStm& left);

#ifndef SWIG
    /// Construct from an initializer list of statements, \a l.
    Seq(std::initializer_list<rStm> l);
#endif /* ! SWIG */

    /// Construct an empty statement list.
    Seq() = default;

    /** \} */

    /** \name Accessors.
     ** \{ */

    /// children.
    const tree_list_type& children_get() const;
    tree_list_type& children_get();

    /** \} */

    /// Append a statement to the statement list.
    void emplace_back(const rStm& stm);

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream&) const override;
    std::ostream& dump(std::ostream& ostr) const override;

    /** \} */

    /// Iterating.
    void for_each_child(std::function<void(const rTree&)> f) override;

    /// Variant for matching.
    virtual StmVariant variant(const rStm& ref) override;

  private:
    tree_list_type children_;
  };

} // namespace tree

#include <tree/seq.hxx>
