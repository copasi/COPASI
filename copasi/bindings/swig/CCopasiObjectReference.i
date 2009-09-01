// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiObjectReference.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2009/09/01 13:39:35 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "report/CCopasiObjectReference.h"

%}

%ignore referenceType;


%include "report/CCopasiObjectReference.h"

typedef CCopasiObjectReference<C_FLOAT64> FloatReference;

%template(FloatReference) CCopasiObjectReference<C_FLOAT64>;



