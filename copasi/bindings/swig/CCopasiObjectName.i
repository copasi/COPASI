// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CCopasiObjectName.i,v $ 
//   $Revision: 1.11 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:26 $ 
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

#include <string>
#include "report/CCopasiObjectName.h"

%}

%warnfilter(402) CCopasiObjectName;

%ignore CCopasiObjectName::findEx;
%ignore CRegisteredObjectName::getSet;

%include "report/CCopasiObjectName.h"

%extend CCopasiObjectName
{
  std::string getString()
  {
   return *self;
  }
}



