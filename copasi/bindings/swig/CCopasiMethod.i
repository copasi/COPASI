// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiMethod.i,v $ 
//   $Revision: 1.8.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/03 15:42:42 $ 
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

%{

#include "utilities/CCopasiMethod.h"  

%}

%ignore CCopasiMethod::XMLSubType;
%ignore CCopasiMethod::SubTypeName;

%include "utilities/CCopasiMethod.h"


%extend CCopasiMethod{
  static std::string getSubTypeName(const int& subType)
  {
    return CCopasiMethod::SubTypeName[subType];
  }

  static int TypeNameToEnum(const std::string& typeName)
  {
     return toEnum(typeName.c_str(), CCopasiMethod::XMLSubType, CCopasiMethod::unset); 
  }
}



