// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 


%{

#include "copasi/sensitivities/CSensTask.h"

%}

// process is ignored because I have written extension code in CCopasiTask
// that calls the task specific process, so this new process should be
// used for all tasks
%ignore CSensTask::process(const bool& useInitialValues);
%ignore CSensTask::initialize;
%ignore CSensTask::print;
%ignore operator<<(std::ostrean&,const CSensTask&);

#ifdef SWIGR
// we ignore the method that takes an int and create a new method that takes
// the enum from CCopasiTask
%ignore CSensTask::setMethodType(const int& type);
#endif // SWIGR


%newobject CSensTask::createMethod(const int &) const;

%include "sensitivities/CSensTask.h"

%extend CSensTask{

#ifdef SWIGR
  bool setMethodType(const CTaskEnum::Method& type)
   {
      return $self->setMethodType(type);
   }
#endif // SWIGR
}




