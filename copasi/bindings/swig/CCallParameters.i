// Begin CVS Header 
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CCallParameters.i,v $ 
//   $Revision: 1.2 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2010/07/16 18:56:27 $ 
// End CVS Header 

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
