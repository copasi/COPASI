// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 




%{

#include <string>
#include "core/CCommonName.h"

%}


%ignore CCommonName::findEx;
%ignore CRegisteredCommonName::getSet;

%include "std_string.i"
%include "core/CCommonName.h"

%extend CCommonName
{
  std::string getString()
  {
   return *self;
  }
}



