/**
 ** \file tree/call.cc
 ** \brief Implementation for tree/call.hh.
 **/

#include <misc/indent.hh>
#include <tree/call.hh>
#include <tree/trees.hh>

namespace tree
{

  Call::Call(const rExp& func, const std::list<rExp>& args)
    : Exp()
  {
    child_push_back(func);

    for (const rExp& exp : args)
      child_push_back(exp);
  }

  std::ostream&
  Call::tag_print(std::ostream&) const
  {
    unreached();
  }

  std::ostream&
  Call::dump(std::ostream& ostr) const
  {
    return ostr << "call"
                << misc::incendl
                << children_get()
                << misc::decendl
                << "call end";
  }

  Tree::kind_tree_type
  Call::kind_get() const
  {
    return call_kind;
  }

}
