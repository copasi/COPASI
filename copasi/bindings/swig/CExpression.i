// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CExpression.i,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/04 19:28:43 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{
#include "function/CExpression.h"
%}

%newobject CEvaluationTree::createInitialExpression;

%include "function/CExpression.h"


