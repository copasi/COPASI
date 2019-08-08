// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 







%{

#include <string>
#include "copasi/core/CCommonName.h"
#include "copasi/core/CRegisteredCommonName.h"

%}


%ignore CCommonName::findEx;
%ignore CRegisteredCommonName::getSet;

%include "std_string.i"
%include "std_vector.i"

%include "copasi/core/CCommonName.h"
%include "copasi/core/CRegisteredCommonName.h"

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
