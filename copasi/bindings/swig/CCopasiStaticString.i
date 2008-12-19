// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiStaticString.i,v $ 
//   $Revision: 1.4.24.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/18 10:37:24 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "report/CCopasiStaticString.h"

%}  

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CCopasiStaticString::operator =;
%ignore CCopasiReportSeparator::operator =;

#endif // SWIGJAVA


%include "report/CCopasiStaticString.h"


