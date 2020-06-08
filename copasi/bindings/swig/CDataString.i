// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

%{

#include "copasi/core/CDataString.h"

%}  

%ignore CDataString::print;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CDataString::operator =;
%ignore CCopasiReportSeparator::operator =;

#endif // SWIGJAVA || CSHARP


%include "copasi/core/CDataString.h"


