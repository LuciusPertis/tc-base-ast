// -*- C++ -*-

%module tiger_temp

%include "std_string.i"
%include "std_map.i"
%include "std_list.i"

%{
  #include <list>
  #include <map>
  #include <temp/libtemp.hh>
  #include <misc/endomap.hh>
  #include <temp/label.hh>
%}

%include "temp/libtemp.hh"

// Show only a simplified version of TempMap.
// We need it to instantiate easily a TempMap object in Python.

namespace temp {
  class TempMap {};
  class Temp {};
  class Label {};
}

%extend temp::TempMap
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}

%extend temp::Temp
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}

%extend temp::Label
{
  std::string __str__() const
  {
    std::ostringstream o;
    o << *$self;
    return o.str();
  }
}
