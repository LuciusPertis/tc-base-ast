// -*- C++ -*-

%module tiger_liveness

%include "std_string.i"

%import "tiger_misc.i"

%{
  #include <misc/error.hh>
  #include <liveness/libliveness.hh>
%}

%include "liveness/libliveness.hh"
