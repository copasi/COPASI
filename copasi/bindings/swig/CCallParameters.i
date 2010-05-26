// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCallParameters.i,v $ 
//   $Revision: 1.1.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/26 17:45:12 $ 
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
%ignore CFunctionParameterMap::getObjects() const;
%ignore CFunctionParameterMap::removeCallParameter;
%ignore CFunctionParameterMap::getObjects;

%include "function/CCallParameters.h" 

%template(PointerCallParameters) CCallParameters<C_FLOAT64>;
typedef CCallParameters<C_FLOAT64> PointerCallParameters;
%template(ObjectCallParameters) CCallParameters<CCopasiObject>;
typedef CCallParameters<CCopasiObject> ObjectCallParameters;



