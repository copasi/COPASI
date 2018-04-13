// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 







%{

#include <string>
#include "core/CCommonName.h"
#include "core/CRegisteredCommonName.h"

%}


%ignore CCommonName::findEx;
%ignore CRegisteredCommonName::getSet;

%include "std_string.i"
%include "std_vector.i"

%include "core/CCommonName.h"
%include "core/CRegisteredCommonName.h"

%extend CCommonName
{
  std::string getString()
  {
   return *self;
  }
}



namespace std {
%template(ReportItemVector) vector<CRegisteredCommonName>;
%template(VectorOfReportItemVectors) vector< vector<CRegisteredCommonName> >;
}
