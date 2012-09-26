// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CFitTask.h"

%}

// process is ignored because I have written extension code in CCopasiTask
// that calls the task specific process, so this new process should be
// used for all tasks
%ignore CFitTask::process(const bool& useInitialValues);
%ignore CFitTask::initialize;
%ignore CFitTask::ValidMethods;

#ifdef SWIGR
// we ignore the method that takes an int and create a new method that takes
// the enum from CCopasiTask
%ignore CFitTask::setMethodType(const int& type);
#endif // SWIGR

%include "parameterFitting/CFitTask.h"

%extend CFitTask{
  std::vector<C_INT32> getValidMethods() const
    {
      std::vector<C_INT32> validMethods;
      unsigned int i=0;
      while($self->ValidMethods[i]!=CCopasiMethod::unset)
      {
        validMethods.push_back($self->ValidMethods[i]);
        i++;
      }
      return validMethods;
    } 
   
#ifdef SWIGR
   bool setMethodType(const CCopasiMethod::SubType& type)
   {
      return $self->setMethodType(type);
   }
#endif // SWIGR
}



