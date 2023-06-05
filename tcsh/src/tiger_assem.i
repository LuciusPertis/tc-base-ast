// -*- C++ -*-

%module tiger_assem

%include "std_shared_ptr.i"
%include "std_string.i"

%ignore assem::operator<<;

%ignore misc::ref::operator=;
%include "misc/ref.hh"

%{
  #include "helper.hh"
  #include <sstream>
  #include <assem/fragment.hh>
  #include <assem/fragments.hh>
  #include <assem/libassem.hh>
  #include <assem/fwd.hh>
  #include <assem/visitor.hh>
%}

%typemap(ret) assem::Fragment* {
  $result = get_swig_real_fragment_type(*$1);
}

%typemap(ret) assem::Instr* {
  $result = get_swig_real_instr_type(*$1);
}
%apply assem::Instr* { assem::Instr }

%include "std_vector.i"
%template (FragmentVector) std::vector<assem::Fragment*>;
%template (InstrVector) std::vector<assem::Instr*>;

%include "assem/fwd.hh"

%extend assem::Fragments
{
  %rename(_print) print(std::ostream&);
  std::string __str__() const
  {
    std::ostringstream o;
    o << *($self);
    return o.str();
  }
}

%extend assem::Fragment
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *($self);
    return o.str();
  }
}

%{
namespace {
  using namespace assem;
  class SwigTypeVisitor : public ConstVisitor
  {
    public:
      PyObject *result;

#define STHELPER(TYPE) STCONVERT(TYPE, p_assem__ ## TYPE)
    STHELPER(DataFrag)
    STHELPER(ProcFrag)
#undef STHELPER
  };
} // namespace

PyObject *get_swig_real_fragment_type(const assem::Fragment& e)
{
  SwigTypeVisitor stv;
  e.accept(stv);
  return stv.result;
}
%}

%extend assem::Instrs
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *($self);
    return o.str();
  }
}

%extend assem::Instr
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *($self);
    return o.str();
  }
}

%{
PyObject *get_swig_real_instr_type(const assem::Instr& e)
{
  PyObject *result = nullptr;
  using namespace assem;
#define STHELPER(TYPE) IFTYPECONVERT(TYPE, p_assem__ ## TYPE)
  STHELPER(Comment)
  STHELPER(Label)
  STHELPER(Move)
  STHELPER(Oper)
#undef STHELPER
  return result;
}
%}

%include "assem/instr.hh"

%include "assem/comment.hh"
%include "assem/label.hh"
%include "assem/move.hh"
%include "assem/oper.hh"

%ignore assem::Instrs::operator=;
%include "assem/instrs.hh"

%include "assem/fragments.hh"
%include "assem/fragment.hh"

%include "assem/libassem.hh"
