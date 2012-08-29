// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CTrajectoryMethod.i,v $ 
//   $Revision: 1.8 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:26 $ 
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


