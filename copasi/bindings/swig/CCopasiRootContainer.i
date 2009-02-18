// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiRootContainer.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/02/18 20:59:34 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "report/CCopasiRootContainer.h"

%}



%ignore CCopasiRootContainer::CCopasiRootContainer(const std::string& name,
                                           const CCopasiRootContainer * pParent = NULL,
                                           const std::string & type = "CN",
                                           const unsigned C_INT32 & flag);

%immutable CCopasiRootContainer::Root;

%rename (RootContainer) CCopasiRootContainer::Root;

%include "report/CCopasiRootContainer.h"

