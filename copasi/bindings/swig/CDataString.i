// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

%{

#include "core/CDataString.h"

%}  

%ignore CDataString::print;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CDataString::operator =;
%ignore CCopasiReportSeparator::operator =;

#endif // SWIGJAVA || CSHARP


%include "core/CDataString.h"


