// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CScanMethod.i,v $ 
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

#include "scan/CScanMethod.h"

%}

%newobject CScanMethod::createMethod();
%newobject CScanItem::createScanItemFromParameterGroup(const CCopasiParameterGroup* si,CRandom* rg,CSanTask* st);

%ignore CScanMethod::init();

%include "scan/CScanMethod.h"



