/**
 ** \file tree/call.cc
 ** \brief Implementation for tree/call.hh.
 **/

#include <misc/indent.hh>
#include <misc/separator.hh>
#include <tree/call.hh>
#include <tree/trees.hh>

namespace tree
{
  Call::Call(const rExp& func, const tree_list_type& args)
    : Exp()
    , func_(func)
    , args_(args)
  {
    for_each_child([&](const rTree& child) { child->parent_set(this); });
  }

  std::ostream& Call::tag_print(std::ostream&) const { unreachable(); }

  std::ostream& Call::dump(std::ostream& ostr) const
  {
    return ostr << "call" << misc::incendl << *func_ << misc::iendl << args_
                << misc::decendl << "call end";
  }

  void Call::for_each_child(std::function<void(const rTree&)> f)
  {
    f(func_);

    for (const auto& arg : args_)
      f(arg);
  }

  ExpVariant Call::variant(const rExp& ref) { return rCall(ref.cast<Call>()); }

} // namespace tree
