// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiObject.i,v $ 
//   $Revision: 1.5 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/12/11 21:10:27 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "report/CCopasiObject.h"
%}

%ignore UpdateMethod;
%ignore SpecificUpdateMethod;
%ignore Refresh;
%ignore operator<<(std::ostream& os,const CCopasiObject& o);

%include "report/CCopasiObject.h"

