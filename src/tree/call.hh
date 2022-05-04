/**
 ** \file tree/call.hh
 ** \brief Intermediate representation: call.hh
 **/

#pragma once

#include <iosfwd>
#include <vector>

#include <tree/exp.hh>

namespace tree
{
  class Call : public Exp
  {
  public:
    /** \brief Construct a call to a function.
     **
     ** \param func     Function called
     ** \param args     Arguments of the function, including static link
     **                 if required.
     */
    Call(const rExp& func, const tree_list_type& args);

    /** \name Accessors.
     ** \{ */
    const rExp func_get() const;
    const tree_list_type& args_get() const;
    /** \} */

    /** \name Printing.
     ** \{ */

    std::ostream& tag_print(std::ostream&) const override;

    // Lists need a closer.
    std::ostream& dump(std::ostream& ostr) const override;

    /// Iterating.
    void for_each_child(std::function<void(const rTree&)> f) override;

    /// Variant for matching.
    virtual ExpVariant variant(const rExp& ref) override;

    /** \} */
  private:
    const rExp func_;
    const tree_list_type args_;
  };

} // namespace tree

#include <tree/call.hxx>
