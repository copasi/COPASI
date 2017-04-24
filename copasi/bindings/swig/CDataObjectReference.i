// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual 
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

%include "core/CDataObjectReference.h"

typedef CDataObjectReference<C_FLOAT64> FloatReference;

%template(FloatReference) CDataObjectReference<C_FLOAT64>;



