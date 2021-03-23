/**
 ** \file tree/tree.hh
 ** \brief Declaration of tree::Tree.
 **/

#pragma once

#include <iosfwd>

#include <temp/temp.hh>
#include <tree/fwd.hh>

namespace tree
{
  class Tree
  {
  public:
    /// A fresh node.
    Tree();
    /// Recursively destroy the children.
    virtual ~Tree();

    // parent
    void parent_get_assert() const;
    Tree* parent_get();
    const Tree* parent_get() const;
    void parent_set(Tree* parent);

    /// Report on \a o the kind of this instruction.
    virtual std::ostream& tag_print(std::ostream& o) const = 0;
    /// Report this instruction on \a o.
    virtual std::ostream& dump(std::ostream& o) const = 0;

    // temp::Temp management for asm output.
    temp::Temp& asm_get();
    void asm_set(const temp::Temp& temp);

    // State management for asm output.
    void* state_get() const;
    void*& state_get();

    /// Call \a f on each child of this node.
    virtual void for_each_child(std::function<void(const rTree&)> f) = 0;

    // Reduced state.
    bool reducible_get() const;
    void reducible_set(bool b);

  protected:
    friend std::ostream& operator<<(std::ostream& ostr, const Tree& tree);

    /// The Tree instruction this is a child from.
    Tree* parent_ = nullptr;
    /// The Temp for asm output.
    temp::Temp* temp_ = nullptr;
    /// The state for asm output.
    void* state_ = nullptr;
    /// Tell if the tree is reducible.
    bool reducible_ = true;
  };

  /// Print \a t on \a o.
  std::ostream& operator<<(std::ostream& o, const Tree& t);

} // namespace tree

#include <tree/tree.hxx>
