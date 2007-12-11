// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CLyapMethod.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/12/11 21:10:27 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "lyap/CLyapMethod.h"

%}

%newobject CLyapMethod::createMethod(CCopasiMethod::SubType subType);
%ignore CLyapValidSubTypes;


%ignore CLyapMethod::ValidSubTypes;

%template(MethodSubTypeVector) std::vector<CCopasiMethod::SubType>;

%include "lyap/CLyapMethod.h"



