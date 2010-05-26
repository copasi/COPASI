// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CSteadyStateTask.i,v $ 
//   $Revision: 1.5.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/26 16:15:01 $ 
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

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CSteadyStateTask.h"

%}

%ignore operator<<(std::ostream &os, const CSteadyStateTask &A);
%ignore CSteadyStateTask::process(const bool& useInitialValues);
%ignore CSteadyStateTask::initialize(const OutputFlag & of, std::ostream * pOstream);
%ignore CSteadyStateTask::load;

%rename (getResult) CSteadyStateTask::getResult() const; // unignore %getResult()

%include "steadystate/CSteadyStateTask.h"


