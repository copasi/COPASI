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

#include "function/CFunction.h"

%}

%ignore operator<<;
%ignore CFunction::operator==;
%ignore CFunction::load;
%ignore CFunction::dependsOn;
%ignore CFunction::splitFunction;
%ignore CFunction::writeMathML;

// suppress warnings on multiple inheritance
%warnfilter(813) CFunction;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CFunction::getVariables() const;

#endif // SWIGJAVA || CSHARP

%include "function/CFunction.h" 



