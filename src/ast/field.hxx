/**
 ** \file ast/field.hxx
 ** \brief Inline methods of ast::Field.
 */

#ifndef AST_FIELD_HXX
# define AST_FIELD_HXX

# include <ast/field.hh>

namespace ast
{


  inline const misc::symbol&
  Field::name_get() const
  {
    return name_;
  }
  inline void
  Field::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const NameTy&
  Field::type_name_get() const
  {
    return *type_name_;
  }
  inline NameTy&
  Field::type_name_get()
  {
    return *type_name_;
  }


} // namespace ast

#endif // !AST_FIELD_HXX
