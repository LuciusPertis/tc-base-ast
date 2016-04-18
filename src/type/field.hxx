/**
 ** \file type/field.hxx
 ** \brief Inline methods for type::Field.
 */
#pragma once

#include <type/field.hh>
#include <misc/contract.hh>

namespace type
{
  inline
  Field::Field(misc::symbol name, const Type& type)
    : name_(name)
    , type_(type)
  {}

  inline misc::symbol
  Field::name_get() const
  {
    return name_;
  }

  inline const Type&
  Field::type_get() const
  {
    return type_;
  }

} // namespace type
