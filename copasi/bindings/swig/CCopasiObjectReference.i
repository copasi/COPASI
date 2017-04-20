// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

%{

#include "copasi/core/CDataObjectReference.h"

%}

%ignore referenceType;
%ignore CDataObjectReference::getValuePointer;
%ignore CDataObjectReference::setReference;
%ignore CDataObjectReference::CDataObjectReference;
%ignore CDataObjectReference::print;

%include "report/CDataObjectReference.h"

typedef CDataObjectReference<C_FLOAT64> FloatReference;

%template(FloatReference) CDataObjectReference<C_FLOAT64>;



