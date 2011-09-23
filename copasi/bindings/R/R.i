// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/R/R.i,v $ 
//   $Revision: 1.1.2.7 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/23 14:59:22 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 



// the following typemap replaces the default in typemap for enum references
// because I think the default typemap has a bug
%typemap(scoercein) const enum SWIGTYPE &
  %{
      $input = enumToInteger($input, "$*1_mangle"); 
  %}

// the following typemap replaces the default scoerceout typemap for enum references
// because I think the default typemap has a bug
%typemap(scoerceout) const enum SWIGTYPE &
  %{
      $result = enumFromInteger($result, "$*1_mangle"); 
  %}


// this seems to fix the problem that size_t references are
// used as pointers
%typemap("rtype") size_t, size_t*, size_t& "numeric";

// the swig rtype.swg file handles bool and bool*, but there is nothing
// about references to bool values, which probably means that there are 
// converted to pointers
// This should fix this problem and treat them as logical values
%typemap("rtype") bool, bool*, const bool *, bool &, const bool &    "logical";


%include "../swig/copasi.i"

%{
#include "report/CCopasiRootContainer.h"
#include "commandline/COptions.h"
%}

%init %{

// Taken from CopasiSE.cpp

// Create the root container
CCopasiRootContainer::init(0,NULL,false);

%}



