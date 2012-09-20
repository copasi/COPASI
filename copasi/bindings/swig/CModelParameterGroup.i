// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/bindings/swig/CModelParameterGroup.i,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: bergmann $
//   $Date: 2011/05/03 13:53:19 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

%ignore CModelParameterGroup::begin() const;
%ignore CModelParameterGroup::end() const;

%{

#include "model/CModelParameterGroup.h"

%}


%include "model/CModelParameterGroup.h"



