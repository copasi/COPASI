// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/COptProblem.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2007/12/12 14:53:31 $ 
// End CVS Header 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "optimization/COptProblem.h"

%}


%ignore operator<<(std::ostream& os, const COptProblem& o);

%ignore COptProblem::getVariableSize() const;

%template(FloatCVector) CVector<C_FLOAT64>;

%include "optimization/COptProblem.h"

