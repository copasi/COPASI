// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 


%{

#include "optimization/COptTask.h"

%}

// process is ignored because I have written extension code in CCopasiTask
// that calls the task specific process, so this new process should be
// used for all tasks
%ignore COptTask::process(const bool& useInitialValues);
%ignore COptTask::ValidMethods;
%ignore COptTask::initialize;

#ifdef SWIGR
// we ignore the method that takes an int and create a new method that takes
// the enum from CCopasiTask
%ignore COptTask::setMethodType(const int& type);
#endif // SWIGR



%include "optimization/COptTask.h"

%extend COptTask{
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


