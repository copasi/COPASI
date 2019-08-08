// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

%{

#include "copasi/core/CDataObjectReference.h"

%}

%ignore referenceType;
%ignore CDataObjectReference::getValuePointer;
%ignore CDataObjectReference::setReference;
%ignore CDataObjectReference::CDataObjectReference;
%ignore CDataObjectReference::print;

%include "copasi/core/CDataObjectReference.h"

typedef CDataObjectReference<C_FLOAT64> FloatReference;

%template(FloatReference) CDataObjectReference<C_FLOAT64>;



