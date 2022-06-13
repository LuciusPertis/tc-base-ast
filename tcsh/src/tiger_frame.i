// -*- C++ -*-

%module tiger_frame

%include "std_string.i"

%{
  #include <frame/fwd.hh>
  #include <frame/access.hh>
  #include <frame/frame.hh>
%}

%ignore frame::Frame::operator=;

%include "frame/fwd.hh"
%include "frame/frame.hh"

%extend frame::Access
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *($self);
    return o.str();
  }
}
%extend frame::Frame
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *($self);
    return o.str();
  }
}
