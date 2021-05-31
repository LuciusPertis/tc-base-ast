// -*- C++ -*-

%module tiger_liveness

%{
  #include <liveness/libliveness.hh>
%}

%include "liveness/libliveness.hh"
// FIXME: These wrappers are workaround for SWIG/Python unable to
// automatically convert a char* to a std::string.
%inline
{
  namespace liveness
  {
    void
    flowgraph_dump (const char* filename,
                    const assem::Fragments& fragments,
                    misc::timer& timer)
    {
      flowgraph_dump (std::string (filename), fragments, timer);
    }

    void
    liveness_dump (const char* filename,
                   const assem::Fragments& fragments,
                   const temp::TempMap& tempmap,
                   misc::timer& timer)
    {
      liveness_dump (std::string (filename), fragments, tempmap, timer);
    }

    void
    interference_dump (const char* filename,
                       const assem::Fragments& fragments,
                       const temp::TempMap& tempmap,
                       misc::timer& timer)
    {
      interference_dump (std::string (filename), fragments, tempmap, timer);
    }
  }
}
