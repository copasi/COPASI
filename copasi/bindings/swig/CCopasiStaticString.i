// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "core/CDataString.h"

%}  

%ignore CCopasiStaticString::print;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CCopasiStaticString::operator =;
%ignore CCopasiReportSeparator::operator =;

#endif // SWIGJAVA || CSHARP


%include "core/CDataString.h"


