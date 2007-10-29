// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CSteadyStateTask.i,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2007/10/29 13:17:16 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "steadystate/CSteadyStateTask.h"

%}

%ignore operator<<(std::ostream &os, const CSteadyStateTask &A);


%include "steadystate/CSteadyStateTask.h"

