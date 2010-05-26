// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CTrajectoryMethod.i,v $ 
//   $Revision: 1.7.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/26 17:45:12 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

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

%ignore CTrajectoryMethod::getRoots;

%include "trajectory/CTrajectoryMethod.h"


