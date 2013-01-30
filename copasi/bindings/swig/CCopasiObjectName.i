// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
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

#include <string>
#include "report/CCopasiObjectName.h"

%}


%ignore CCopasiObjectName::findEx;
%ignore CRegisteredObjectName::getSet;

%include "std_string.i"
%include "report/CCopasiObjectName.h"

%extend CCopasiObjectName
{
  std::string getString()
  {
   return *self;
  }
}



