// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "trajectory/CTrajectoryTask.h"

%}

%ignore CTrajectoryTask::load;
%ignore CTrajectoryTask::initialize;
#ifdef SWIGR
// we ignore the method that takes an int and create a new method that takes
// the enum from CCopasiTask
%ignore CTrajectoryTask::setMethodType(const int& type);
#endif // SWIGR

%include "trajectory/CTrajectoryTask.h"

%extend CTrajectoryTask{
  std::vector<C_INT32> getValidMethods() const
    {
		  const CTaskEnum::Method *methods = $self->getValidMethods();
			
      std::vector<C_INT32> validMethods;
      unsigned int i=0;
      while(methods!=CTaskEnum::UnsetMethod)
      {
        validMethods.push_back(methods[i]);
        ++i;
      }
      return validMethods;
    } 

#ifdef SWIGR
   bool setMethodType(const CTaskEnum::Method& type)
   {
      return $self->setMethodType(type);
   }
#endif // SWIGR
}




