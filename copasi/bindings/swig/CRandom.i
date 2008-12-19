// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CRandom.i,v $ 
//   $Revision: 1.2.14.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/12 15:18:48 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "randomGenerator/CRandom.h"

%}

%newobject CRandom::createGenerator(CRandom::Type type = CRandom::mt19937, unsigned C_INT32 seed = 0);
%ignore CRandom::varp;
%ignore CRandom::vare;
%ignore CRandom::XMLType;

%include "randomGenerator/CRandom.h"



