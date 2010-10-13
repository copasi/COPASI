// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CSensMethod.i,v $ 
//   $Revision: 1.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/10/13 12:03:01 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "sensitivities/CSensMethod.h"

%}

%newobject CTrajectoryMethod::createSensMethod(CCopasiMethod::SubType subType = CCopasiMethod::sensMethod);

%include "sensitivities/CSensMethod.h"


