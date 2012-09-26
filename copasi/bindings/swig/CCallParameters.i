// Begin git Header 
//   Commit: 28d5663ff3fc99993d3b249dec626841cb5247ab 
//   Author: Frank T. Bergmann fbergman@caltech.edu 
//   Date: 2012-08-29 10:43:00 +0200 
// End git Header 


// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

%{

#include "function/CCallParameters.h"

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

%include "function/CCallParameters.h" 

%template(PointerCallParameters) CCallParameters<C_FLOAT64>;
typedef CCallParameters<C_FLOAT64> PointerCallParameters;
%template(ObjectCallParameters) CCallParameters<CCopasiObject>;
typedef CCallParameters<CCopasiObject> ObjectCallParameters;

// unignore findParameterByName
%rename(findParameterByName) CFunctionParameterMap::findParameterByName;

%extend CFunctionParameterMap
{
  unsigned C_INT32 findParameterbyName(const std::string& name, CFunctionParameter::DataType dataType)
  {
    return $self->findParameterByName(name,dataType);
  }
}
