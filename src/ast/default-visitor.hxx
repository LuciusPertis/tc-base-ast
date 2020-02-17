/**
 ** \file ast/default-visitor.hxx
 ** \brief Implementation for ast/default-visitor.hh.
 */

#pragma once

#include <ast/all.hh>
#include <ast/default-visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  template <template <typename> class Const>
  GenDefaultVisitor<Const>::GenDefaultVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenDefaultVisitor<Const>::~GenDefaultVisitor()
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<Ast>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<SimpleVar>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FieldVar>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<CastVar>& e)
  {
    e.var_get().accept(*this);
    e.ty_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<SubscriptVar>& e)
  {
    e.var_get().accept(*this);
    e.index_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<NilExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<IntExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<StringExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<CallExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<OpExp>& e)
  {
    e.left_get().accept(*this);
    e.right_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<RecordExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<SeqExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<AssignExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<IfExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<WhileExp>& e)
  {
    e.test_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ForExp>& e)
  {
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    e.body_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<BreakExp>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<LetExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ArrayExp>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<CastExp>& e)
  {
    e.exp_get().accept(*this);
    e.ty_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FieldInit>& e)
  {
    e.init_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<DecsList>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<Decs>& e)
  {
    e.accept(*this);
  }

  template <template <typename> class Const>
  template <typename DecsType>
  inline void GenDefaultVisitor<Const>::decs_visit(const_t<DecsType>& e)
  {
    // The compiler cannot know whether the entity `type' is a type
    // or some other kind.  We must help it by specifying `typename'.

    // The type of the argument of this function, with const preserved.
    using arg_type = const_t<DecsType>;
    // The type of the list contained by this argument, const preserved.
    // We need to use Const again, because getting a typedef from
    // a const class does not give a const typedef.
    using elt_type = const_t<typename arg_type::Ds>;
    // An iterator over this list, const_iterator if needed.
    // "auto" power!
    typename misc::select_iterator<elt_type>::type i;
    for (i = e.decs_get().begin(); i != e.decs_get().end(); ++i)
      (*i)->accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<VarDecs>& e)
  {
    decs_visit<VarDecs>(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<VarDec>& e)
  {
    // `type_name' might be omitted.
    this->accept(e.type_name_get());
    // `init' can be null in case of formal parameter.
    this->accept(e.init_get());
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FunctionDecs>& e)
  {
    decs_visit<FunctionDecs>(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<FunctionDec>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<TypeDecs>& e)
  {
    decs_visit<TypeDecs>(e);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<TypeDec>& e)
  {
    e.ty_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<NameTy>&)
  {}

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<RecordTy>& e)
  {
  // FIXME: Some code was deleted here.
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<ArrayTy>& e)
  {
    e.base_type_get().accept(*this);
  }

  template <template <typename> class Const>
  void GenDefaultVisitor<Const>::operator()(const_t<Field>& e)
  {
    e.type_name_get().accept(*this);
  }

} // namespace ast
