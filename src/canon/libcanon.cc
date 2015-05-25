/**
 ** \file canon/libcanon.cc
 ** \brief Simplify HIR into LIR.
 */

#include <tree/fragment.hh>
#include <tree/fragments.hh>
#include <canon/canon.hh>
#include <canon/traces.hh>
#include <canon/libcanon.hh>

namespace canon
{

  void
  canonicalize(tree::Fragments& fragments, bool canon_trace_p)
  {
    class CanonVisitor : public tree::Visitor
    {
    public:
      using tree::Visitor::operator();

      CanonVisitor(bool trace_p)
        : canon_(trace_p)
      {}

      virtual void operator()(tree::ProcFrag& frag)
      {
        frag.body_set(canon_(frag.body_get()));
      }

    private:
      canon::Canon canon_;
    };

    CanonVisitor visitor(canon_trace_p);
    visitor(fragments);
  }


  void
  make_traces(tree::Fragments& fragments, bool trace_trace_p)
  {
  // FIXME: Some code was deleted here (Invoke Traces on each ProcFrag).
  }


} // namespace canon
