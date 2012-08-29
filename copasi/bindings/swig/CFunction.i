// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CFunction.i,v $ 
//   $Revision: 1.6 $ 
//   $Name:  $ 
//   $Author: bergmann $ 
//   $Date: 2012/04/11 15:40:26 $ 
// End CVS Header 

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
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

#include "function/CFunction.h"

%}

%ignore operator<<;
%ignore CFunction::load;
%ignore CFunction::dependsOn;
%ignore CFunction::splitFunction;
%ignore CFunction::writeMathML;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CFunction::getVariables() const;

#endif // SWIGJAVA || CSHARP

%include "function/CFunction.h" 



