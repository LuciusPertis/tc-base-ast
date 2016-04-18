/**
 ** \file object/renamer.hh
 ** \brief Implementation of object::Renamer.
 */

#pragma once

#include <map>

#include <bind/renamer.hh>
#include <object/libobject.hh>

namespace object
{
  /// \brief Perform identifier renaming within an AST (in place),
  /// with support for objects.
  class Renamer : public bind::Renamer
  {
  public:
    using super_type = ::bind::Renamer;

    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build a Renamer.
    Renamer();

    // Visit methods.
  public:
    /// \name Visiting definition sites.
    /// \{
    /// This method is like bind::Binder's, but prevent the renaming
    /// of attributes.
    void operator()(ast::VarDec& e) override;
    /// Rename methods.
    void operator()(ast::MethodDecs& e) override;
    /// Rename a method.
    void operator()(ast::MethodDec& e) override;
    /// In addition to performing the renaming, collect the name of
    /// the classes.
    void operator()(ast::TypeDecs& e) override;
    /// \}

    /// \name Visiting usage sites.
    /// \{
    void operator()(ast::MethodCallExp& e) override;
    /// \}

    /// \name Visiting other object-related nodes.
    ///
    /// These methods should be part of an ObjectDefaultVisitor, but
    /// our current design makes the implementation (and the use) of
    /// such a visitor difficult.
    /// \{
    void operator()(ast::ClassTy& e) override;
    void operator()(ast::ObjectExp& e) override;
    /// \}

    /// \name Visiting other non-object related nodes.
    ///
    /// These method are just wrappers around their homonyms from
    /// bind::Renamer, handling \a within_class_ty_.
    /// \{
    void operator()(ast::ForExp& e) override;
    void operator()(ast::FunctionDec& e) override;
    /// \}

    /// Class names.
    /// \{
  public:
    /// Get the class names.
    class_names_type* class_names_get() const;

  private:
    /// Dictionnary mapping class types to their names.
    class_names_type* class_names_;
    /// Are we in a class definition?
    bool within_class_ty_;
    /// \}
  };

} // namespace object
