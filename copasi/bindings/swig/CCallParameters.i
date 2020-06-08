// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%{

#include "copasi/function/CCallParameters.h"

%}

%ignore CCallParameters::operator[];
%ignore CCallParameters::begin;
%ignore CCallParameters::end;
%ignore CCallParameters::push_back;
%ignore CFunctionParameterMap::getObjects() const;
%ignore CFunctionParameterMap::removeCallParameter;
%ignore CFunctionParameterMap::getObjects;
%ignore CFunctionParameterMap::findParameterByName;
%ignore CFunctionParameterMap::pUnmappedObject;
%ignore CFunctionParameterMap::getPointers() const;

// suppress warnings on nested structures
%warnfilter(325) UType;

%include "copasi/function/CCallParameters.h" 

%template(PointerCallParameters) CCallParameters<C_FLOAT64>;
typedef CCallParameters<C_FLOAT64> PointerCallParameters;
%template(ObjectCallParameters) CCallParameters<CDataObject>;
typedef CCallParameters<CDataObject> ObjectCallParameters;

// unignore findParameterByName
// %rename(findParameterByName) CFunctionParameterMap::findParameterByName;
// 
// %extend CFunctionParameterMap
// {
//   unsigned C_INT32 findParameterbyName(const std::string& name, CFunctionParameter::DataType dataType)
//   {
//     return (unsigned C_INT32)$self->findParameterByName(name,dataType);
//   }
// }
