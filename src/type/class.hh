/**
 ** \file type/class.hh
 ** \brief The class Class.
 */
#ifndef TYPE_CLASS_HH
# define TYPE_CLASS_HH

# include <list>

# include <misc/symbol.hh>
# include <type/attribute.hh>
# include <type/method.hh>
# include <type/type.hh>

namespace type
{
  /** \brief Class types.
   **
   ** List of Attributes and Methods. */
  class Class : public Type
  {
    /** \name Constructor.
     ** \{ */
  public:
    /** \brief Construct a Class.
     **
     ** \param super Super class. */
    Class(const Class* super = nullptr);
    /** \} */

    /** \name Attribute and Method elementary manipulation.
     ** \{ */
  public:
    /// Return the attribute type associated to \a key.
    const Type* attr_type(const misc::symbol& key) const;
    /// Return the method type associated to \a key.
    const Method* meth_type(const misc::symbol& key) const;
    /** \} */

    /** \name Internal Attribute list manipulators.
     ** \{ */
  public:
    /// List of Attribute's.
    typedef std::list<Attribute> attrs_type;
    /// List of Method's.
    typedef std::list<const Method*> meths_type;

    /// Return the list of stored Attributes (read only).
    const attrs_type& attrs_get() const;
    /// Return the list of stored Methods (read only).
    const meths_type& meths_get() const;

    /// \brief Find an attribute using its name, return `nullptr' if
    /// not found.
    ///
    /// The search is performed throughtout the super classes.
    const Attribute* attr_find(const misc::symbol& key) const;
    /// \brief Find an owned attribute using its name, return
    /// `nullptr' if not found.
    ///
    /// The search is restricted to the class.
    const Attribute* owned_attr_find(const misc::symbol& key) const;

    /// \brief Find an owned method using its name, return `nullptr'
    /// if not found.
    ///
    /// The search is restricted to the class.
    const Method* owned_meth_find(const misc::symbol& key) const;

    /// Add an already existing Attribute to the list.
    void attr_add(const Attribute& attr);
    /// Create a Attribute then add it to the list.
    void attr_add(const ast::VarDec* def);

    /// Add an already existing Method to the list.
    void meth_add(const Method* method);
    /** \} */

    /// Does this class have actual data (i.e., owned attributes)?
    bool has_data() const;

    /** \name Accessors.
     ** \{ */
  public:
    /// Return the unique identifier of the class.
    unsigned id_get() const;

    /// Return the type of the super class.
    const Class* super_get() const;
    /// Set the type of the super class.
    void super_set(const Class* type);

    /// Return (the transitive closure of) the list of subclasses.
    const std::list<const Class*>& subclasses_get() const;

    /// \brief Add a class to the list of subclasses.
    ///
    /// Although this method alters \a this, it is const, since types
    /// are mostly manipulated as const entities.
    void subclass_add(const Class* subclass) const;

    /// \brief Erase all the subclasses.
    ///
    /// This method is const for the same reason as
    /// type::Class::subclass_add.
    void subclasses_clear() const;
    /** \} */

    /** \name Type resolution.
     ** \{ */
  public:
    /** \brief Check that the definition of this class is sound,
     ** i.e. that there is no recursive inheritance.  */
    bool sound() const;
    /** \} */

  // FIXME: Some code was deleted here (Inherited virtual methods).

  public:
    /// Return the unique instance of the class type `Object'.
    static const Class& object_instance();

  private:
    /// Return a fresh identifier.
    static unsigned fresh_id();

    /// Class unique identifier
    unsigned id_;
    /// Super class.
    const Class* super_;
    /// Sub classes.
    mutable std::list<const Class*> subclasses_;
    /// Attributes list.
    attrs_type attrs_;
    /// Methods list.
    meths_type meths_;
  };


} // namespace type

# include <type/class.hxx>

#endif // !TYPE_CLASS_HH
