// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

//#include "copasi/steadystate/CSteadyStateMethod.h"
#include "copasi/steadystate/CMCATask.h"

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

%include "copasi/steadystate/CMCATask.h"

   
#ifdef SWIGR
%extend CMCATask{
    bool setMethodType(const CTaskEnum::Method& type)
   {
      return $self->setMethodType(type);
   }
}
#endif // SWIGR

