// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/COptProblem.i,v $ 
//   $Revision: 1.2.20.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/28 13:38:45 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "optimization/COptProblem.h"

%}

typedef std::vector<COptItem*> OptItemStdVector;

%ignore operator<<(std::ostream& os, const COptProblem& o);

%ignore COptProblem::getVariableSize() const;
%ignore COptProblem::setCallBack;
%ignore COptProblem::getCalculateVariableUpdateMethods;

%template(FloatCVector) CVector<C_FLOAT64>;

%include "optimization/COptProblem.h"

