// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CModelValue.i,v $ 
//   $Revision: 1.8.8.2 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:56:12 $ 
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

%include "model/CModelValue.h"


