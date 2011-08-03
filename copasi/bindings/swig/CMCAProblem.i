// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMCAProblem.i,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/08/03 09:33:37 $ 
// End CVS Header 

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "steadystate/CMCAProblem.h"

%}

%ignore CMCAProblem::load;
%ignore CMCAProblem::printResult;
%ignore CMCAProblem::print;
%ignore operator<<(std::ostream& os,const CMCAProblem& o);

%include "steadystate/CMCAProblem.h"

