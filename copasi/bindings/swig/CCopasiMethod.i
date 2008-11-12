// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiMethod.i,v $ 
//   $Revision: 1.7.6.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:56:12 $ 
// End CVS Header 

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

%include "utilities/CCopasiMethod.h"


%extend CCopasiMethod{
  static const std::string& getSubTypeName(const int& subType)
  {
    return CCopasiMethod::SubTypeName[subType];
  }
}



