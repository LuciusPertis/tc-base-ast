/**
 ** \file assem/visitor.hh
 ** \brief Allow to visit assembly fragments.
 */

#pragma once

#include <assem/fwd.hh>
#include <misc/select-const.hh>

namespace assem
{
  template <template <typename> class Const> class GenVisitor
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Convenient abbreviation.
    template <typename Type> using const_t = typename Const<Type>::type;

    /// Destroy a Visitor
    virtual ~GenVisitor() = default;
    /** \} */

  public:
    /// Visit an assembly procedure fragment.
    virtual void operator()(const_t<ProcFrag>& a);
    /// Visit an assembly data fragment.
    virtual void operator()(const_t<DataFrag>& a);
    /// To enable the use of standard algorithm on containers of pointers.
    template <class E> void operator()(E* e);

    /// Visit a list of assembly fragments.
    virtual void operator()(const_t<Fragments>& fs);
  };

  /// Readonly visitor.
  using ConstVisitor = GenVisitor<misc::constify_traits>;
  /// Read-write visitor.
  using Visitor = GenVisitor<misc::id_traits>;

} // namespace assem

#include <assem/visitor.hxx>
