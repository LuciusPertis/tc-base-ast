// -*- C++ -*-

%module tiger_tree

%include "std_shared_ptr.i"
%include "std_string.i"
%include "std_vector.i"

%import "tiger_temp.i"
%import "tiger_frame.i"

%ignore tree::operator<<(std::ostream& ostr, const tree::Tree& tree);
%ignore tree::Tree::operator<<(std::ostream& ostr, const tree::Tree& tree);

%warnfilter(401); // hide misc::ref errors

%{
  #include "helper.hh"
  #include <sstream>
  #include <tree/fragment.hh>
  #include <tree/fragments.hh>
  #include <tree/libtree.hh>
  #include <misc/ref.hh>
  #include <tree/fwd.hh>
  #include <tree/all.hh>
%}

%ignore misc::ref::operator=;
%include "misc/ref.hh"

%typemap(ret) tree::Fragment* {
  $result = get_swig_real_tree_fragment(*$1);
}
%typemap(ret) misc::ref<tree::Tree> {
  $result = get_swig_real_rtree_type($1);
}
%apply misc::ref<tree::Tree> { misc::ref<tree::Stm>, misc::ref<tree::Exp> }
%template (FragmentVector) std::vector<tree::Fragment*>;

%include "tree/visitor.hh"
%template(TreeGenConstVisitor) tree::GenVisitor<misc::constify_traits>;
%template(TreeGenVisitor) tree::GenVisitor<misc::id_traits>;

%include "tree/fwd.hh"

%include "tree/fragments.hh"
%include "tree/fragment.hh"

%extend tree::Fragments
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }

}

%extend tree::Fragment
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}

%{
namespace {
  using namespace tree;
  class SwigTreeFragmentVisitor : public ConstVisitor
  {
    public:
      PyObject *result;

#define STHELPER(TYPE) STCONVERT(TYPE, p_tree__ ## TYPE)
    STHELPER(DataFrag)
    STHELPER(ProcFrag)
#undef STHELPER
  };
} // namespace

PyObject *get_swig_real_tree_fragment(const tree::Fragment& e)
{
  SwigTreeFragmentVisitor stv;
  e.accept(stv);
  return stv.result;
}

%}

%extend tree::Tree
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}

%define DECLARE(What)
%template (r ## What) misc::ref<tree:: ## What>;
%extend misc::ref<tree::What>
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << **$self;
    return o.str();
  }
  tree::What* get() const noexcept {
    return ($self)->get();
  }
}
%enddef

DECLARE(Tree)
DECLARE(Exp)
DECLARE(Stm)
DECLARE(Binop)
DECLARE(Call)
DECLARE(Cjump)
DECLARE(Const)
DECLARE(Eseq)
DECLARE(Jump)
DECLARE(Label)
DECLARE(Mem)
DECLARE(Move)
DECLARE(Name)
DECLARE(Seq)
DECLARE(Sxp)
DECLARE(Temp)

%{
PyObject *get_swig_real_rtree_type(const misc::ref<tree::Tree>& t)
{
  using namespace tree;
#define STHELPER(TYPE)                                                         \
  if (auto e = t.unsafe_cast<TYPE>())                                          \
    return SWIG_NewPointerObj(new misc::ref<TYPE>(e),                          \
                              SWIGTYPE_p_misc__refT_tree__ ## TYPE ## _t,      \
                              SWIG_POINTER_OWN);

  STHELPER(Binop)
  STHELPER(Call)
  STHELPER(Cjump)
  STHELPER(Const)
  STHELPER(Eseq)
  STHELPER(Jump)
  STHELPER(Label)
  STHELPER(Mem)
  STHELPER(Move)
  STHELPER(Name)
  STHELPER(Seq)
  STHELPER(Sxp)
  STHELPER(Temp)
  STHELPER(Exp)
  STHELPER(Stm)
  STHELPER(Tree)
#undef STHELPER
  return NULL;
}

%}

%ignore tree::Tree::state_get();
%include "tree/tree.hh"

%include "tree/exp.hh"
%include "tree/stm.hh"

%include "tree/binop.hh"
%include "tree/call.hh"
%include "tree/cjump.hh"
%include "tree/const.hh"
%include "tree/eseq.hh"
%include "tree/jump.hh"
%include "tree/label.hh"
%include "tree/mem.hh"
%include "tree/move.hh"
%include "tree/name.hh"
%include "tree/seq.hh"
%include "tree/sxp.hh"
%include "tree/temp.hh"

%include "tree/libtree.hh"

