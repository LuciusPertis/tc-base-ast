/**
 ** \file type/named.hh
 ** \brief The class Named.
 */
#ifndef TYPE_NAMED_HH
# define TYPE_NAMED_HH

# include <misc/symbol.hh>
# include <type/type.hh>
# include <type/fwd.hh>

namespace type
{
  /** \brief Named types.
   **
   ** Named types are used when new types are defined, i.e., in
   ** \b Example: let type name_ = type_.
   */
  class Named : public Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /** \brief Construct a Named type.
     ** \param name user defined type's identifier. */
    Named(misc::symbol name);
    /** \brief Construct a Named type.
     ** \param name user defined type's identifier.
     ** \param type defined type's structure */
    Named(misc::symbol name, const Type* type);
    /// Destroy this object, but not the Type pointed to.
    ~Named();
    /** \} */


    /** \name Accessors.
     ** \{ */
  public:
    /// Return the user defined type's structure.
    const Type* type_get() const;

    /// Set the defined type's structure.
    void type_set(const Type* type);

    /** \brief Set the defined type's structure.
     **
     ** This is the version which is used by TypeChecker which needs to
     ** assign a value to the Named type. */
    void type_set(const Type* type) const;

    /// Return the name of this type.
    misc::symbol name_get() const;

    /// (Re)set the name of this type.
    void name_set(const misc::symbol& name);
    /** \} */


    /** \name Type resolution.
     ** \{ */
  public:
    /// The type pointed to ultimately.
    virtual const Type& actual() const override;

    /** \brief Check that the definition of this named type is sound,
     ** i.e. that there is no recursive dependency.  */
    bool sound() const;
    /** \} */

    virtual bool compatible_with(const Type& other) const override;

  public:
    /// Print type redirections.
    virtual std::ostream& dump(std::ostream& ostr) const override;

  protected:
    /// Name of the defined type.
    misc::symbol name_;

    /** \brief The Type pointed to.
     **
     ** "Mutable const" because most of the time types are handled as
     ** const objects.  But Named types are built in two steps: first
     ** they are built without any value for \a type_ (by
     ** TypeChecker::visit_dec_header <ast::FunctionDec>), and then
     ** they are completed (by TypeChecker::visit_dec_body <ast::FunctionDec>).
     ** Because the second step of the construction is actually seen
     ** as a modification by the C++ type system, we have it accept
     ** it thanks to mutable.
     **/
    mutable const Type* type_;
  };


} // namespace type

# include <type/named.hxx>

#endif // !TYPE_NAMED_HH
