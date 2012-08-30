// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CCopasiObjectReference.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "report/CCopasiObjectReference.h"

%}

%ignore referenceType;
%ignore CCopasiObjectReference::getValuePointer;
%ignore CCopasiObjectReference::setReference;
%ignore CCopasiObjectReference::CCopasiObjectReference;
%ignore CCopasiObjectReference::print;

%include "report/CCopasiObjectReference.h"

typedef CCopasiObjectReference<C_FLOAT64> FloatReference;

%template(FloatReference) CCopasiObjectReference<C_FLOAT64>;



