// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMCATask.i,v $ 
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

//#include "steadystate/CSteadyStateMethod.h"
#include "steadystate/CMCATask.h"

%}


%newobject CMCAMethod::createMethod(const int& type) const;

%ignore CMCATask::process(const bool& useInitialValues);
%ignore CMCATask::initialize;
%ignore CMCATask::load;
%ignore CMCATask::print;
%ignore CMCATask::printResult;

%ignore operator<<(std::ostream&,const CMCATask&);

%include "steadystate/CMCATask.h"


