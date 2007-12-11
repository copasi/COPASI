// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CScanProblem.i,v $ 
//   $Revision: 1.2 $ 
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

#include "scan/CScanProblem.h"

%}

%newobject CScanProblem::createScanItem(CScanProblem::Type type, unsigned C_INT32 steps = 5, const CCopasiObject* obj = NULL);

%ignore CScanProblem::getScanItemType(unsigned C_INT32 index);
%ignore getScanItem(unsigned C_INT32 index) const;

%include "scan/CScanProblem.h"



