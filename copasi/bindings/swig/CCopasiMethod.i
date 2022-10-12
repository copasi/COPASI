// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/utilities/CTaskEnum.h"  
#include "copasi/utilities/CCopasiMethod.h"  

%}



%newobject CCopasiMethod::createMethod(const CDataContainer * pParent,
                                      const CTaskEnum::Method & methodType,
                                      const CTaskEnum::Task & taskType);

%ignore operator<<;
%ignore CCopasiMethod::XMLSubType;
%ignore CTaskEnum::MethodName;
%ignore CTaskEnum::MethodXML;
%ignore CTaskEnum::TaskXML;
%ignore CCopasiMethod::SubTypeName;
//%ignore CCopasiMethod::setCallBack;
%ignore CCopasiMethod::load;
%ignore CCopasiMethod::print;
%ignore CCopasiMethod::printResult;

%include "copasi/utilities/CCopasiMethod.h"
%include "copasi/utilities/CTaskEnum.h"


%extend CCopasiMethod
{
  
  virtual bool setCallBack(CProcessReport *pHandler)
  {
    return self->setCallBack(CProcessReportLevel(pHandler));
  }
  
  static std::string getSubTypeName(const int& subType)
  {
    return CTaskEnum::MethodName[subType];
  }

  static int TypeNameToEnum(const std::string& typeName)
  {
     return static_cast< int >(CTaskEnum::MethodName.toEnum(typeName, CTaskEnum::Method::UnsetMethod)); 
  }
}
