// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiTask.i,v $ 
//   $Revision: 1.25.2.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/05/15 18:58:58 $ 
// End CVS Header 

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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
%ignore CCopasiTask::TypeName;
%ignore CCopasiTask::ValidMethods;
%ignore CCopasiTask::process(bool const &);
%ignore CCopasiTask::getCallBack;
%ignore CCopasiTask::setCallBack;
%ignore CCopasiTask::isValidMethod;
%ignore CCopasiTask::initialize;

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CCopasiTask::getProblem() const;
%ignore CCopasiTask::getMethod() const;

// SWIG does not wrap this correctly in JAVA 
%ignore CCopasiTask::eOutputFlagBase;
%ignore CCopasiTask::NO_OUTPUT;
%ignore CCopasiTask::OUTPUT;
%ignore CCopasiTask::OUTPUT_BEFORE;
%ignore CCopasiTask::OUTPUT_AFTER;
%ignore CCopasiTask::OUTPUT_SE;
%ignore CCopasiTask::OUTPUT_UI;
%ignore CCopasiTask::ONLY_TIME_SERIES;

#endif // SWIGJAVA


%include "utilities/CCopasiTask.h"

#ifdef SWIGJAVA
%rename (NO_OUTPUT) CCopasiTask::NO_OUTPUT;
%rename (OUTPUT_BEFORE) CCopasiTask::OUTPUT_BEFORE;
%rename (OUTPUT_AFTER) CCopasiTask::OUTPUT_AFTER;
%rename (OUTPUT) CCopasiTask::OUTPUT;
%rename (OUTPUT_SE) CCopasiTask::OUTPUT_SE;
%rename (OUTPUT_UI) CCopasiTask::OUTPUT_UI;
%rename (ONLY_TIME_SERIES) CCopasiTask::ONLY_TIME_SERIES;
#endif //SWIGJAVA


%extend CCopasiTask{
  #ifdef SWIGJAVA
  // this has to be checked each time the bindings are released
  static const unsigned int CCopasiTask::NO_OUTPUT=0;
  static const unsigned int CCopasiTask::OUTPUT_BEFORE=1;
  static const unsigned int CCopasiTask::OUTPUT_AFTER=2;
  static const unsigned int CCopasiTask::OUTPUT=50;
  static const unsigned int CCopasiTask::OUTPUT_SE=55;
  static const unsigned int CCopasiTask::OUTPUT_UI=119;
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
        bool result=self->initialize(CCopasiTask::OUTPUT_UI,pDataModel, NULL);
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





