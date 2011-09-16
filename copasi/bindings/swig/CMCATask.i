// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMCATask.i,v $ 
//   $Revision: 1.1.2.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/16 16:13:16 $ 
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

// process is ignored because I have written extension code in CCopasiTask
// that calls the task specific process, so this new process should be
// used for all tasks
%ignore CMCATask::process(const bool& useInitialValues);
%ignore CMCATask::initialize;
%ignore CMCATask::load;
%ignore CMCATask::print;
%ignore CMCATask::printResult;

#ifdef SWIGR
// we ignore the method that takes an int and create a new method that takes
// the enum from CCopasiTask
%ignore CMCATask::setMethodType(const int& type);
#endif // SWIGR


%ignore operator<<(std::ostream&,const CMCATask&);

%include "steadystate/CMCATask.h"

   
#ifdef SWIGR
%extend CMCATask{
    bool setMethodType(const CCopasiMethod::SubType& type)
   {
      return $self->setMethodType(type);
   }
}
#endif // SWIGR

