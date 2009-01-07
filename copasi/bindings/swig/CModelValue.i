// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CModelValue.i,v $ 
//   $Revision: 1.9 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "model/CModelValue.h"

%}

%nodefaultctor CModelEntity;
%nodefaultdtor CModelEntity;

%ignore CModelEntity::XMLStatus;

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CModelEntity::getExpressionPtr() const;
%ignore CModelEntity::getInitialExpressionPtr() const;

#endif // SWIGJAVA


%include "model/CModelValue.h"


