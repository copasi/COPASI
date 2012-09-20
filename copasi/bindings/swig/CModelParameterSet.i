// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CModelParameterSet.i,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: bergmann $
//   $Date: 2011/05/03 13:53:19 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

%ignore CModelParameterSet::setModel;
%warnfilter(813) CModelParameterSet;

#if SWIGCSHARP

%csmethodmodifiers  CModelParameterSet::getName  "public new"
%csmethodmodifiers  CModelParameterSet::updateModel  "public new"


#endif

%{

#include "model/CModelParameterSet.h"

%}


%include "model/CModelParameterSet.h"



