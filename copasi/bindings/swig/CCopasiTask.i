// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiTask.i,v $ 
//   $Revision: 1.24.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/26 16:15:01 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

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
%ignore CCopasiTask::getCallBack;
%ignore CCopasiTask::setCallBack;
%ignore CCopasiTask::isValidMethod;

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CCopasiTask::getProblem() const;
%ignore CCopasiTask::getMethod() const;

// SWIG does not wrap this correctly in JAVA 
%ignore CCopasiTask::NO_OUTPUT;
%ignore CCopasiTask::OUTPUT;
%ignore CCopasiTask::OUTPUT_COMPLETE;
%ignore CCopasiTask::ONLY_TIME_SERIES;

#endif // SWIGJAVA


%include "utilities/CCopasiTask.h"

#ifdef SWIGJAVA
%rename (NO_OUTPUT) CCopasiTask::NO_OUTPUT;
%rename (OUTPUT) CCopasiTask::OUTPUT;
%rename (OUTPUT_COMPLETE) CCopasiTask::OUTPUT_COMPLETE;
%rename (ONLY_TIME_SERIES) CCopasiTask::ONLY_TIME_SERIES;
#endif //SWIGJAVA


%extend CCopasiTask{
  #ifdef SWIGJAVA
  // this has to be checked each time the bindings are released
  static const unsigned int CCopasiTask::NO_OUTPUT=0;
  static const unsigned int CCopasiTask::OUTPUT=114;
  static const unsigned int CCopasiTask::OUTPUT_COMPLETE=119;
  static const unsigned int CCopasiTask::ONLY_TIME_SERIES=71;

  #endif //SWIGJAVA

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
        CCopasiDataModel* pDataModel=self->getObjectDataModel();
        assert(pDataModel!=NULL);
        bool result=self->initialize(CCopasiTask::OUTPUT_COMPLETE,pDataModel, NULL);
        if(result)
        {
          result=self->process(useInitialValues);
          pDataModel->finish();
        }
        if(result)
        {
          result=self->restore();
        }
        return result;
      }  
   
}  





