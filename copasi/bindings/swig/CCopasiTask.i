// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiTask.i,v $ 
//   $Revision: 1.21.6.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/17 08:50:57 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%include exception.i

%{
#include <exception>
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiException.h"
%}

%catches(CCopasiException) CCopasiTask::process();

%ignore CCopasiTask::getDescription() const;
%ignore CCopasiTask::getResult() const;
%ignore CCopasiTask::XMLType;
%ignore CCopasiTask::ValidMethods;
%ignore CCopasiTask::process(bool const &);
%ignore CCopasiTask::OutputFlag;

%include "utilities/CCopasiTask.h"


%extend CCopasiTask{
  std::vector<C_INT32> getValidMethods() const
    {
      std::vector<C_INT32> validMethods;
      unsigned int i=0;
      while(self->ValidMethods[i]!=CCopasiMethod::unset)
      {
        validMethods.push_back(self->ValidMethods[i]);
        i++;
      }
      return validMethods;
    } 

    virtual  bool process(bool useInitialValues) 
      {
        CCopasiMessage::clearDeque();
        bool result=self->initialize(CCopasiTask::OUTPUT_COMPLETE,CCopasiDataModel::Global, NULL);
        if(result)
        {
          result=self->process(useInitialValues);
          CCopasiDataModel::Global->finish();
        }
        if(result)
        {
          result=self->restore();
        }
        return result;
      }  
   
}  





