// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CTrajectoryMethod.i,v $ 
//   $Revision: 1.6.24.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/15 21:53:05 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "trajectory/CTrajectoryMethod.h"

%}

%newobject CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType = CCopasiMethod::deterministic,CTrajectoryProblem * pProblem = NULL);

%include "trajectory/CTrajectoryMethod.h"


