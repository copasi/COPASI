// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CScanProblem.i,v $ 
//   $Revision: 1.3 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CScanProblem::getScanItem(unsigned C_INT32 index) const;

%include "scan/CScanProblem.h"



