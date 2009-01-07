// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CFitTask.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "parameterFitting/CFitTask.h"

%}

%ignore CFitTask::process(const bool& useInitialValues);
%ignore CFitTask::initialize;
%ignore CFitTask::ValidMethods;

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
}



